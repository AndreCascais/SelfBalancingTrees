#include <iostream>
#include <string.h>
#include <map>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

//@todo overload operador == entre nodes ?

class Node {
public:
    Node(int value);
    ~Node();
    int get_height();
    void update_height();
    int get_height_diff();
    int get_value();
    void set_left(Node* n);
    Node* get_left();
    void set_right(Node* n);
    Node* get_right();
    void set_father(Node* n);
    Node* get_father();
    void set_son(Node* n);
	void delete_son(Node* n);
	
	Node* get_max();
	Node* get_min();
    void print_node();

private:
    int height;
    int value;
    Node* left;
    Node* right;
    Node* father;
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void iterate_tree();
    void destroy_tree();
    void add_value(int v);
    void remove_value(int v);

private:
    void destroy_tree(Node* node);
    void delete_node(Node* node);
    Node* find_value(Node* node, int v);
    Node* add_value(Node* node, int v);
    Node* remove_node(Node* node);
    void traverse_backwards(Node* node);
    Node* root;
};

Node::Node(int v) {
    value = v;
    height = 0;
    left = NULL;
    right = NULL;
    father = NULL;
}

Node::~Node() {
}

int Node::get_value() {
    return value;
}

int Node::get_height() {
    return height;
}

void Node::update_height() {
    int height_left = (this->get_left() == NULL ? -1 : this->get_left()->get_height());
    int height_right = (this->get_right() == NULL ? -1 : this->get_right()->get_height());
    height = 1 + max(height_left, height_right);
}

int Node::get_height_diff() {
    Node* left = this->get_left();
    Node* right = this->get_right();
    int left_height = (left == NULL ? -1 : left->get_height());
    int right_height = (right == NULL ? -1 : right->get_height());

    return right_height - left_height;
}

void Node::set_left(Node* n) {
    if (n != NULL) {
        n->set_father(this);
    }
    left = n;
}

Node* Node::get_left() {
    return left;
}

void Node::set_right(Node* n) {
    if (n != NULL) {
        n->set_father(this);
    }
    right = n;
}

Node* Node::get_right() {
    return right;
}

void Node::set_father(Node* n) {
    father = n;
}

Node* Node::get_father() {
    return father;
}

void Node::set_son(Node* n) {
    if (n != NULL) { // Have to also update either left or right
        int val = n->get_value();
        if (val > this->value) { //right
            this->set_right(n);
        }
        else { //left
            this->set_left(n);
        }
    }
	else
		this->set_right(NULL); //@todo hack much ?
}

void Node::delete_son(Node* n) {
	Node* left_node = n->get_left();
	if (left_node != NULL && left_node->get_value() == n->get_value())
		this->set_left(NULL);
	else
		this->set_right(NULL);
		
}

Node* Node::get_max() {
	if (this->get_right() == NULL)
		return this;
	else 
		return this->get_right()->get_max();
}

Node* Node::get_min() {
	if (this->get_left() == NULL)
		return this;
	else 
		return this->get_left()->get_min();
}

void Node::print_node() {
    printf("I am at %d my height is %d height diff is %d\n", this->get_value(), this->get_height(),
           this->get_height_diff());
}

AVLTree::AVLTree() {
    root = NULL;
}

AVLTree::~AVLTree() {
}

void AVLTree::add_value(int v) {
    printf("adding %d\n", v);
    if (root == NULL) {
        root = new Node(v);
    } else {
        Node* new_node = add_value(root, v);
        traverse_backwards(new_node->get_father());
    }

}

void AVLTree::destroy_tree() {
	destroy_tree(root);
}

void AVLTree::destroy_tree(Node* node) {
	if (node != NULL) {
		destroy_tree(node->get_left());
		destroy_tree(node->get_right());
		delete node;
	}
}

void AVLTree::remove_value(int v) {
    printf("removing %d\n", v);
    Node* found_node = find_value(root, v);
	if (found_node != NULL)
		printf("found val\n");
	else 
		printf("null\n");
	Node* father = remove_node(found_node);
	if (father != NULL) {
		printf("going back on %d\n", father->get_value());
    	traverse_backwards(father);
	}
}

Node* AVLTree::add_value(Node* node, int v) { // Assumir valores diferentes a serem inseridos
    int value = node->get_value();
    if (v > value) {// Right
        Node* node_right = node->get_right();
        if (node_right == NULL) {
            Node* new_node = new Node(v);
            node->set_right(new_node);
            return new_node;
        } else {
            return add_value(node_right, v);
        }
    } else { // Left
        Node* node_left = node->get_left();
        if (node_left == NULL) {
            Node* new_node = new Node(v);
            node->set_left(new_node);
            return new_node;
        } else {
            return add_value(node_left, v);
        }
    }

}

Node* AVLTree::find_value(Node* node, int v) {
    int value = node->get_value();
    if (v == value) {
        return node;
    }
    else {
        Node* new_node = (v > value) ? node->get_right() : node->get_left();
        if (new_node == NULL) {
            return NULL;
        }
        else {
            return find_value(new_node, v);
        }
    }
}

Node* AVLTree::remove_node(Node* node) {

	Node* father = node->get_father();
	Node* left_node = node->get_left();
	Node* right_node = node->get_right();
    if (node->get_height() == 0) { // leaf
		printf("leaf\n");
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
		Node* new_root = left_node->get_max();
		Node* backtrack_node = new_root->get_father();
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
    
void AVLTree::traverse_backwards(Node* node) {
	// @todo definir rotacoes e usar combinações para cada caso
    node->update_height();
    Node* father = node->get_father();
    
    int diff = node->get_height_diff();

    if (diff < -1) { // left deeper
        int left_diff = node->get_left()->get_height_diff();

        if (left_diff <= 0) {// left -> left case1 @ example if both heights are now equal we keep going in the same direction (left)
            printf("case1\n");
            Node* new_root = node->get_left();
            new_root->set_father(father);
            if (father != NULL) // set father podia fazer as duas coisas
                father->set_son(new_root);
            
            Node* temp = new_root->get_right();

            new_root->set_right(node);
            node->set_left(temp);
            node->update_height();
            node = new_root;
        } 
		else { // left -> right case3 @ example
			printf("case3\n");
            Node* new_root = node->get_left()->get_right();
            new_root->set_father(father);
            if (father != NULL)
                father->set_son(new_root);
            
            Node* temp_left = new_root->get_left();
            Node* temp_right = new_root->get_right();
            
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
            Node* new_root  = node->get_right()->get_left();
            new_root->set_father(father);
            if (father != NULL)
                father->set_son(new_root);
            Node* temp_left = new_root->get_left();
            Node* temp_right = new_root->get_right();
            
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
            Node* new_root = node->get_right();
            new_root->set_father(father);
            if (father != NULL) {
                printf("seting son\n");
                father->set_son(new_root);
            }
            
            Node* temp = new_root->get_left();
            
            new_root->set_left(node);
            node->set_right(temp);
            node->update_height();
            node = new_root;
            
        }
    }

    
    if (father == NULL) {
        root = node;
        return;
    }

    traverse_backwards(father);
}

void AVLTree::iterate_tree() {
    Node* n = root;

	if (n == NULL)
		return;
	
    printf("l - left\n");
    printf("r - right\n");
    printf("f - father\n");
    printf("root - root\n");
    printf("quit - quit\n");
    printf("add - quit\n");
    printf("remove - quit\n");


    char s[10];
    while (1) {

        n->print_node();
        scanf("%s", s);

        if (strcmp(s, "l") == 0) {
            Node* left = n->get_left();
            if (left == NULL)
                printf("Not going to NULL Node\n");
            else
                n = left;
        } else if (strcmp(s, "r") == 0) {
            Node* right = n->get_right();
            if (right == NULL)
                printf("Not going to NULL Node\n");
            else
                n = right;
        } else if (strcmp(s, "f") == 0) {
            if (n == root)
                printf("Already at root\n");
            else
                n = n->get_father();
        } else if (strcmp(s, "root") == 0) {
            n = root;
        } else if (strcmp(s, "quit") == 0) {
			this->destroy_tree();
            return;
        } else if (strcmp(s, "add") == 0) {
            int v;
            scanf("%d", &v);
            this->add_value(v);
        } else if (strcmp(s, "remove") == 0) {
            int v;
            scanf("%d", &v);
            this->add_value(v);
        } else
            printf("Unknown cmd\n");
    }
}

int main(int arc, char** argv) {
    //AVLTree *a = new AVLTree;
    AVLTree* t = new AVLTree();
	
	/*t->add_value(6);
	t->add_value(2);
	t->add_value(8);
	t->add_value(1);
	t->add_value(4);
	t->add_value(9);
	t->add_value(3);
	t->remove_value(9);*/
   	t->add_value(2);
    t->add_value(78);
    t->add_value(49);
    t->add_value(50);
    t->add_value(21);
    t->add_value(34);
    t->add_value(36);
    t->add_value(81);
    t->add_value(14);
    t->add_value(70);
	t->remove_value(34);
	t->remove_value(49);

    t->iterate_tree();
	delete t;
    return 0;
}

		