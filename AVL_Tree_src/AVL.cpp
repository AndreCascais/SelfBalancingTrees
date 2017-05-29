#include <iostream>
#include <string.h>
#include <map>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

//@todo overload operador == entre nodes ?

FILE* file = NULL;


template <class T> class Node {
public:
    Node(T value);
    ~Node();
	
    int get_height();
    void update_height();
    int get_height_diff();
    T get_value();
    void set_left(Node<T>*);
    Node<T>* get_left();
    void set_right(Node<T>*);
    Node<T>* get_right();
    void set_father(Node<T>*);
    Node<T>* get_father();
    void set_son(Node<T>*);
	void delete_son(Node<T>*);
	
	Node<T>* get_min();
	Node<T>* get_max();
    void print_node();

private:
    T height;
    T value;
    Node<T>* left;
    Node<T>* right;
    Node<T>* father;
};

template <class T> class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void iterate_tree();
    void destroy_tree();
    void add_value(T);
    void remove_value(T);

private:
    void destroy_tree(Node<T>*);
    void delete_node(Node<T>* );
    Node<T>* find_value(Node<T>*, T);
	Node<T>* rotate_right(Node<T>*);
	Node<T>* rotate_left(Node<T>*);
    Node<T>* add_value(Node<T>*, T);
    Node<T>* remove_node(Node<T>*);
    void traverse_backwards(Node<T>*);
	
    Node<T>* root;
};

template <class T> Node<T>::Node(T v) {
    value = v;
    height = 0;
    left = NULL;
    right = NULL;
    father = NULL;
}

template <class T> Node<T>::~Node() {
}

template <class T> T Node<T>::get_value() {
    return value;
}

template <class T> int Node<T>::get_height() {
    return height;
}

template <class T> void Node<T>::update_height() {
	Node<T>* left = this->get_left();
    Node<T>* right = this->get_right();
    int height_left = (left == NULL ? -1 : left->get_height());
    int height_right = (right == NULL ? -1 : right->get_height());
    height = 1 + max(height_left, height_right);
}

template <class T> int Node<T>::get_height_diff() {
    Node<T>* left = this->get_left();
    Node<T>* right = this->get_right();
    int left_height = (left == NULL ? -1 : left->get_height());
    int right_height = (right == NULL ? -1 : right->get_height());

    return right_height - left_height;
}

template <class T> void Node<T>::set_left(Node<T>* n) {
    if (n != NULL) {
        n->set_father(this);
    }
    left = n;
}

template <class T> Node<T>* Node<T>::get_left() {
    return left;
}

template <class T> void Node<T>::set_right(Node<T>* n) {
    if (n != NULL) {
        n->set_father(this);
    }
    right = n;
}

template <class T> Node<T>* Node<T>::get_right() {
    return right;
}

template <class T> void Node<T>::set_father(Node<T>* n) {
    father = n;
}

template <class T> Node<T>* Node<T>::get_father() {
    return father;
}

template <class T> void Node<T>::set_son(Node<T>* n) {
    if (n != NULL) { // Have to also update either left or right
        T val = n->get_value();
        if (val > this->value) { //right
            this->set_right(n);
        }
        else { //left
            this->set_left(n);
        }
    } 
	else { // only gets here when we want to set right to null
		this->set_right(NULL); //@todo hack much ?
	}
}

template <class T> void Node<T>::delete_son(Node<T>* n) { // deletes link only
	Node<T>* left_node = n->get_left();
	if (left_node != NULL && left_node->get_value() == n->get_value()) {
		this->set_left(NULL);
    }
	else {
		this->set_right(NULL);
    }	
}

template <class T> Node<T>* Node<T>::get_max() {
	Node<T>* right = this->get_right();
	if (right == NULL)
		return this;
	else 
		return right->get_max();
}

template <class T> Node<T>* Node<T>::get_min() {
	Node<T>* left = this->get_left();
	if (left == NULL)
		return this;
	else 
		return left->get_min();
}

template <class T> void Node<T>::print_node() {
    //printf("I am at %d my height is %d height diff is %d\n", this->get_value(), this->get_height(),
    //       this->get_height_diff());
    cout << "I am at " << this->get_value() << " my height is " << this->get_height() <<
        " height diff is " << this->get_height_diff() << endl;
}

template <class T> AVLTree<T>::AVLTree() {
    root = NULL;
}

template <class T> AVLTree<T>::~AVLTree() {
}

template <class T> void AVLTree<T>::add_value(T v) {
    cout << "Adding " << v << endl;
    if (root == NULL) {
        root = new Node<T>(v);
    }
	else {
        Node<T>* new_node = add_value(root, v);
        traverse_backwards(new_node->get_father());
    }

}

template <class T> void AVLTree<T>::destroy_tree() {
	destroy_tree(root);
}

template <class T> void AVLTree<T>::destroy_tree(Node<T>* node) {
	if (node != NULL) {
		destroy_tree(node->get_left());
		destroy_tree(node->get_right());
		delete node;
	}
}

template <class T> void AVLTree<T>::remove_value(T v) {
    cout << "Removing " << v << endl;
    Node<T>* found_node = find_value(root, v);
	if (found_node != NULL) {
		Node<T>* backtrack_node = remove_node(found_node);
		if (backtrack_node != NULL) {
			traverse_backwards(backtrack_node);
		}
	}
}

template <class T> Node<T>* AVLTree<T>::rotate_left(Node<T>* node_x) {
	
	Node<T>* node_y;

    node_y = node_x->get_right();
    node_x->set_right(node_y->get_left());

    node_y->set_father(node_x->get_father());

    if (node_y->get_father() == NULL) {
        root = node_y;
    }
    else {
        node_x->get_father()->set_son(node_y);
    }

    node_y->set_left(node_x);
}

template <class T> Node<T>* AVLTree<T>::rotate_right(Node<T>* node_x) {
	
	Node<T>* node_y;
	
	node_y = node_x->get_left();
	node_x->set_left(node_y->get_right());
	
	node_y->set_father(node_x->get_father());
	
	if (node_y->get_father() == NULL) {
		root = node_y;
	}
	else {
		node_x->get_father()->set_son(node_y);
	}
	node_y->set_right(node_x);
}

template <class T> Node<T>* AVLTree<T>::add_value(Node<T>* node, T v) { // Assumir valores diferentes a serem inseridos
    T value = node->get_value();
    if (v > value) {// Right
        Node<T>* node_right = node->get_right();
        if (node_right == NULL) {
            Node<T>* new_node = new Node<T>(v);
            node->set_right(new_node);
            return new_node;
        } 
        else {
            return add_value(node_right, v);
        }
    } 
    else { // Left
        Node<T>* node_left = node->get_left();
        if (node_left == NULL) {
            Node<T>* new_node = new Node<T>(v);
            node->set_left(new_node);
            return new_node;
        } 
        else {
            return add_value(node_left, v);
        }
    }
}

template <class T> Node<T>* AVLTree<T>::find_value(Node<T>* node, T v) {
    T value = node->get_value();
    if (v == value) {
        return node;
    }
    else {
        Node<T>* new_node = (v > value) ? node->get_right() : node->get_left();
        if (new_node == NULL) {
            return NULL;
        }
        else {
            return find_value(new_node, v);
        }
    }
}

template <class T> Node<T>* AVLTree<T>::remove_node(Node<T>* node) {

	Node<T>* father = node->get_father();
	Node<T>* left_node = node->get_left();
	Node<T>* right_node = node->get_right();
    if (node->get_height() == 0) { // leaf
        if (father == NULL) { // root
            root = NULL;
        }
		else { // have to remove link from father
			father->delete_son(node);
		}
    }
	else if (right_node == NULL) { // only have left son
		if (father == NULL)
			root = left_node;
		else
			father->set_son(left_node);
	}
	else if (left_node == NULL) { // only have right son
		if (father == NULL)
			root = right_node;
		else
			father->set_son(right_node);
	}
	else {	
		Node<T>* new_root = left_node->get_max();
		Node<T>* backtrack_node = new_root->get_father(); // exemplo raul
		if (backtrack_node->get_value() == node->get_value())// exemplo nao raul
			backtrack_node = new_root;
		new_root->get_father()->set_son(new_root->get_left());
		if (father != NULL)
			father->set_son(new_root);
		else {
			new_root->set_father(NULL);
			root = new_root;
		}
		if (left_node->get_value() != new_root->get_value())
			new_root->set_left(left_node);
		else // case where we new root is the left node (dont want cycles)
			new_root->set_left(left_node->get_left());
		new_root->set_right(right_node);
		delete node;
		return backtrack_node;
		
	}
	delete node;
	return father;
}
    
template <class T> void AVLTree<T>::traverse_backwards(Node<T>* node) {
	// @todo definir rotacoes e usar combinações para cada caso
    node->update_height();
    Node<T>* father = node->get_father();
    
    int diff = node->get_height_diff();

    if (diff < -1) { // left deeper
        int left_diff = node->get_left()->get_height_diff();

        if (left_diff <= 0) {// left -> left case1 @ example if both heights are now equal we keep going in the same direction (left)
            printf("case1\n");
            Node<T>* new_root = node->get_left();
            new_root->set_father(father);
            if (father != NULL) // set father podia fazer as duas coisas
                father->set_son(new_root);
            
            Node<T>* temp = new_root->get_right();

            new_root->set_right(node);
            node->set_left(temp);
            node->update_height(); // allways updated
			new_root->update_height(); // sometimes only
            node = new_root;
        } 
		else { // left -> right case3 @ example
			printf("case3\n");
            Node<T>* new_root = node->get_left()->get_right();
            new_root->set_father(father);
            if (father != NULL)
                father->set_son(new_root);
            
            Node<T>* temp_left = new_root->get_left();
            Node<T>* temp_right = new_root->get_right();
            
            new_root->set_left(node->get_left());
            new_root->set_right(node);
            
            new_root->get_left()->set_right(temp_left);
            new_root->get_right()->set_left(temp_right);
            
			
			new_root->get_left()->update_height();
			new_root->get_right()->update_height();
            new_root->update_height();
            node = new_root;
        }
        
    }
    else if (diff > 1) { // right deeper
        
        int right_diff = node->get_right()->get_height_diff();
        
        if (right_diff < 0) { // right->left case4
            printf("case4\n");
            Node<T>* new_root  = node->get_right()->get_left();
            new_root->set_father(father);
            if (father != NULL)
                father->set_son(new_root);
            Node<T>* temp_left = new_root->get_left();
            Node<T>* temp_right = new_root->get_right();
            
            new_root->set_left(node);
            new_root->set_right(node->get_right());
            
            new_root->get_left()->set_right(temp_left);
            new_root->get_right()->set_left(temp_right);
           
			new_root->get_left()->update_height();
			new_root->get_right()->update_height();
            new_root->update_height();
            node = new_root;
            
        }
        else { // right->right case2
            printf("case2\n");
            Node<T>* new_root = node->get_right();
            new_root->set_father(father);
            if (father != NULL)
                father->set_son(new_root);
            
            Node<T>* temp = new_root->get_left();
            
            new_root->set_left(node);
            node->set_right(temp);
            node->update_height();
			new_root->update_height();
            node = new_root;
        }
    }
    
    if (father == NULL) {
        root = node;
        return;
    }

    traverse_backwards(father);
}

template <class T> void AVLTree<T>::iterate_tree() {
	
    printf("l - left\n");
    printf("r - right\n");
    printf("f - father\n");
    printf("root - root\n");
    printf("quit - quit\n");
    printf("add - quit\n");
    printf("remove - quit\n");
	
	char s[10];
	if (file != NULL) {
		while (1) {
			fscanf(file, "%s", s);
			if (strcmp(s, "add") == 0) {
				int v;
				fscanf(file, "%d", &v);
				this->add_value(v);
			} 
			else if (strcmp(s, "remove") == 0) {
				int v;
				fscanf(file, "%d", &v);
				this->remove_value(v);
			}
			else if (strcmp(s, "end") == 0)
				break;
		}
	}
	printf("Done reading from file\n");
	Node<T>* n = root;
    while (1) {
	
		if (n != NULL) {
        	n->print_node();
        }
        scanf("%s", s);

        if (strcmp(s, "l") == 0) {
            Node<T>* left = n->get_left();
            if (left == NULL)
                printf("Not going to NULL Node\n");
            else
                n = left;
        } 
        else if (strcmp(s, "r") == 0) {
            Node<T>* right = n->get_right();
            if (right == NULL) {
                printf("Not going to NULL Node\n");
            }
            else {
                n = right;
            }
        } 
        else if (strcmp(s, "f") == 0) {
            if (n == root) {
                printf("Already at root\n");
            }
            else {
                n = n->get_father();
            }
        } 
        else if (strcmp(s, "root") == 0) {
            n = root;
        } 
        else if (strcmp(s, "quit") == 0) {
			this->destroy_tree();
            return;
        } 
		else if (strcmp(s, "add") == 0) {
			int v;
			scanf("%d", &v);
			this->add_value(v);
			n = root;
		} 
		else if (strcmp(s, "remove") == 0) {
			int v;
			scanf("%d", &v);
			this->remove_value(v);
			n = root;
		}
		else {
            printf("Unknown cmd\n");
        }
    }
}

int main(int argc, char** argv) {

	if (argc > 1) {
		file = fopen(argv[1], "r");
	}

    AVLTree<int>* t = new AVLTree<int>();
    t->iterate_tree();
	delete t;
    
    return 0;
}

		