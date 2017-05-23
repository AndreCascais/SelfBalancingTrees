#include <iostream>
#include <string.h>
#include <map>

#include <stdio.h>
#include <stdlib.h>

class Node {
public:
    Node(int value);
    ~Node();
    int get_height();
    void set_height(int h);
    int get_value();
    void set_left(Node* n);
    Node* get_left();
    void set_right(Node* n);
    Node* get_right();
private:
    int height;
    int value;
    Node* left;
    Node* right;
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
	void iterate_tree();
    void destroy_tree();
    void add_value(int n);

private:
    void add_value(Node* node, int n);
    void destroy_tree(Node* node);
    void delete_node(Node* node);
    Node* root;
};

Node::Node(int v) {
    value = v;
    height = 0;
    left = NULL;
    right = NULL;
}

int Node::get_value() {
    return value;
}

int Node::get_height() {
    return height;
}

void Node::set_height(int h) {
    height = h;
}

void Node::set_left(Node* n) {
    left = n;
}

Node* Node::get_left() {
    return left;
}

void Node::set_right(Node* n) {
    right = n;
}

Node* Node::get_right() {
    return right;
}

AVLTree::AVLTree() {
	root = NULL;
}

void AVLTree::add_value(int n) {
	if (root == NULL) {
		printf("Creating root\n");
		root = new Node(n);
	}
	else
		add_value(root, n);
    
}
void AVLTree::add_value(Node* node, int n) { // Assumir valores diferentes a serem inseridos
	int value = node->get_value();
	if (n > value) {// Right
		Node* node_right = node->get_right();
		if (node_right == NULL)
			node->set_right(new Node(n));
		else
			add_value(node_right, n);
	}
	else { // Left
		Node* node_left = node->get_left();
		if (node_left == NULL)
			node->set_left(new Node(n));
		else
			add_value(node_left, n);
	}
    
}

void AVLTree::iterate_tree() {
    Node* n = root;

    printf("l - left\n");
    printf("r - right\n");
    printf("root - root\n");
    printf("quit - quit\n");

    char s[10];
    while (1) {
		
		printf("I am at %d\n", n->get_value());
        scanf("%s", s);

        if (strcmp(s, "l") == 0) {
			Node* left = n->get_left();
            if (left == NULL)
                printf("Not going to NULL Node\n");
            else
                n = left;
        }
        else if (strcmp(s, "r") == 0) {
			Node* right = n->get_right();
            if (right == NULL)
                printf("Not going to NULL Node\n");
            else
                n = right;
        }
        else if (strcmp(s, "root") == 0) {
            n = root;
        }
        else if (strcmp(s, "quit") == 0) {
            return;
        }
        else
            printf("Unknown cmd\n");
    }
}
int main(int arc, char** argv) {
    //AVLTree *a = new AVLTree;
	AVLTree *t = new AVLTree();
	t->add_value(1);
	t->add_value(2);
	t->iterate_tree();
    return 0;
}
