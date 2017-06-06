#include <iostream>
#include <string.h>
#include <map>
#include <tgmath.h>
#include <chrono>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

FILE* file = NULL;

template <class T> class Node {
public:
    Node(T value);
    ~Node();
	
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
    T value;
    Node<T>* left;
    Node<T>* right;
    Node<T>* father;
};

template <class T> class SplayTree {
public:
    SplayTree();
    ~SplayTree();
    void iterate_tree();
    void destroy_tree();
    void add_value(T);
	void remove_value(T v);
	Node<T>* lookup(T v);
	double get_ratio();

private:
    void destroy_tree(Node<T>*);
    void delete_node(Node<T>* );
    Node<T>* find_value(Node<T>*, T);
	void rotate_right(Node<T>*);
	void rotate_left(Node<T>*);
    Node<T>* add_value(Node<T>*, T);
    void remove_root();
    void splay(Node<T>*);
	int get_n_nodes(Node<T>*);
	int	get_height(Node<T>*);
	
    Node<T>* root;
};

template <class T> Node<T>::Node(T v) {
    value = v;
    left = NULL;
    right = NULL;
    father = NULL;
}

template <class T> Node<T>::~Node() {
}

template <class T> T Node<T>::get_value() {
    return value;
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
    
    cout << "I am at " << this->get_value() << endl;
}

template <class T> SplayTree<T>::SplayTree() {
    root = NULL;
}

template <class T> SplayTree<T>::~SplayTree() {
}

template <class T> void SplayTree<T>::add_value(T v) {
    if (root == NULL) {
        root = new Node<T>(v);
    }
	else {
        Node<T>* new_node = add_value(root, v);
        splay(new_node);
    }

}

template <class T> void SplayTree<T>::destroy_tree() {
	destroy_tree(root);
}

template <class T> void SplayTree<T>::destroy_tree(Node<T>* node) {
	if (node != NULL) {
		destroy_tree(node->get_left());
		destroy_tree(node->get_right());
		delete node;
	}
}

template <class T> void SplayTree<T>::remove_value(T v) {
    Node<T>* found_node = find_value(root, v);
	if (found_node != NULL) {
		splay(found_node);
		remove_root();
	}
}

template <class T> void SplayTree<T>::rotate_left(Node<T>* node_x) {
	
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

template <class T> void SplayTree<T>::rotate_right(Node<T>* node_x) {
	
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

template <class T> double SplayTree<T>::get_ratio() {
	int n_nodes = get_n_nodes(root);
	int height = get_height(root);
	return height/(log(n_nodes) / (log(2)));
		
}

template <class T> int SplayTree<T>::get_n_nodes(Node<T>* node) {
	return (node == NULL) ? 0 : 1 + get_n_nodes(node->get_left()) + get_n_nodes(node->get_right());
}

template <class T> int SplayTree<T>::get_height(Node<T>* node) {
	return (node == NULL) ? 0 : 1 + max(get_height(node->get_left()), get_height(node->get_right()));
}

template <class T> Node<T>* SplayTree<T>::add_value(Node<T>* node, T v) { // Assumir valores diferentes a serem inseridos
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

template <class T> Node<T>* SplayTree<T>::lookup(T v) {
	return find_value(root, v);
}

template <class T> Node<T>* SplayTree<T>::find_value(Node<T>* node, T v) {
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

template <class T> void SplayTree<T>::remove_root() {
	
	Node<T>* old_root = root;
	Node<T>* left_node = root->get_left();
	Node<T>* right_node = root->get_right();
	if (left_node == NULL && right_node == NULL) { // only element
		root = NULL;
	}
    else if (left_node == NULL) {
        root = right_node;
		root->set_father(NULL);
    }
	else if (right_node == NULL) { // only have left son
		root = left_node;
		root->set_father(NULL);
	}
	
	else {
				
		Node<T>* new_root = left_node->get_max();
		root = left_node;
			
		splay(new_root);
		root = new_root;
		root->set_right(right_node);
		root->set_father(NULL);
		
	}
	delete old_root;
}
    

template <class T> void SplayTree<T>::splay(Node<T>* node) {

	if (node == root) { // already at root, dont need to splay
		return;
	}
	Node<T>* father = node->get_father();

	if (father->get_father() == NULL) { // zig or zag
		if (father->get_left() == node) {// zig
			rotate_right(father);
		}
		else { // zag
			rotate_left(father);
		}
	}
	else { // zig-zig or zag-zag or zig-zag left/right
		Node<T>* grand_father = father->get_father();
		if (grand_father->get_left() == father) { //zig-zig or zig-zag left
			if (father->get_left() == node) { //zig-zig
				rotate_right(grand_father);
				rotate_right(father);
					
			}
			else { //zig-zag left
				rotate_left(father);
				rotate_right(grand_father);
			}
		}
		else { //zag-zag or zig-zag right
			if (father->get_right() == node) { //zag-zag
				rotate_left(grand_father);
				rotate_left(father);
			}
			else { //zig-zag right
				rotate_right(father);
				rotate_left(grand_father);
			}
		}
	}
    if (node->get_father() == NULL) {
        root = node;
        return;
    }

    splay(node);
}

template <class T> void SplayTree<T>::iterate_tree() {
	
    int i, v, option = 1;
	if (file != NULL) {
		
		int n_inserts, n_removes, n_lookups;
		fscanf(file, "%d%d%d%d", &option, &n_inserts, &n_removes, &n_lookups);
		/*double min_ratio = 100000;
		double max_ratio = 0;
		double avg_ratio = 0;*/
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		for (i = 0; i < n_inserts; i++) {
			fscanf(file, "%d", &v);
			add_value(v);
			/*if (i > 3) {
				double ratio = get_ratio();
				min_ratio = min(ratio, min_ratio);
				max_ratio = max(ratio, max_ratio);
				avg_ratio += ratio;
			}*/
		}
		/*avg_ratio = avg_ratio/(n_inserts - 4);
		printf("min ratio = %lf, max_ratio = %lf, avg_ratio = %lf\n", min_ratio, max_ratio, avg_ratio);*/
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds for insertion"<< std::endl;
		begin = std::chrono::steady_clock::now();
		for (i = 0; i < n_removes; i++) {
			fscanf(file, "%d", &v);
			remove_value(v);
		}
		end = std::chrono::steady_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds for removal"<< std::endl;
		begin = std::chrono::steady_clock::now();
		for (i = 0; i < n_lookups; i++) {
			fscanf(file, "%d", &v);
			lookup(v);
		}
		end = std::chrono::steady_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds for updating"<< std::endl;
	}
	
	if (option == 0) {
		destroy_tree();
		return;
	}
		
	char help_str[] = "Done reading from file\n"
		"l - left\n"
		"r - right\n"
	    "f - father\n"
	    "t - root\n"
	    "q - quit\n"
	    "a v  - adds value v to tree\n"
	    "d v - deletes value v from tree\n";
	
	printf("%s", help_str);
	char cmd;
	
	Node<T>* n = root;
    while (1) {
	
		if (n != NULL) {
        	n->print_node();
        }
        scanf("\n%c", &cmd);
		switch(cmd) {
			case 'l' : {
            	Node<T>* left = n->get_left();
            	if (left == NULL)
                	printf("Not going to NULL Node\n");
            	else
                	n = left;
				break;	
			}
		
			case 'r' : {
				Node<T>* right = n->get_right();
				if (right == NULL) {
					printf("Not going to NULL Node\n");
				}
				else {
					n = right;
				}
				break;	
			}

        	
			case 't' : {
				if (n == root) {
					printf("Already at root\n");
				}
				else {
					n = n->get_father();
				}
			}
			break;
        
			case 'q' : {
				this->destroy_tree();
            	return;
			}
    
			case 'a' : {
				scanf("%d", &v);
				this->add_value(v);
				n = root; 
				
			}
			break;
			case 'd' : {
				scanf("%d", &v);
				this->remove_value(v);
				n = root;
			}
			break;
			default :
            	printf("Unknown cmd\n");
		}
    }
}

int main(int argc, char** argv) {

	if (argc > 1) {
		file = fopen(argv[1], "r");
	}

    SplayTree<int>* t = new SplayTree<int>();
    t->iterate_tree();
	delete t;
    
    return 0;
}
