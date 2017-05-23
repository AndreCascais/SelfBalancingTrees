#include <iostream>
#include <string.h>
#include <map>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Node {
public:
    Node(int value);

    ~Node();

    int get_height();

    void set_height(int h);

    void update_height();

    int get_height_diff();

    int get_value();

    void set_left(Node* n);

    Node* get_left();

    void set_right(Node* n);

    Node* get_right();

    void set_father(Node* n);

    Node* get_father();

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

    void add_value(int n);

private:
    void destroy_tree(Node* node);

    void delete_node(Node* node);

    Node* add_value(Node* node, int n);

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

int Node::get_value() {
    return value;
}

int Node::get_height() {
    return height;
}

void Node::set_height(int h) {
    height = h;
}

void Node::update_height() {
    int height_left = (this->get_left() == NULL ? -1 : this->get_left()->get_height());
    int height_right = (this->get_right() == NULL ? -1 : this->get_right()->get_height());
    height = 1 + max(height_left, height_right);
}

int Node::get_height_diff() {
    Node* left = get_left();
    Node* right = get_right();
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

void Node::print_node() {
    printf("I am at %d my height is %d height diff is %d\n", this->get_value(), this->get_height(),
           this->get_height_diff());
}

AVLTree::AVLTree() {
    root = NULL;
}

void AVLTree::add_value(int v) {
    if (root == NULL) {
        root = new Node(v);
    } else {
        Node* new_node = add_value(root, v);
        traverse_backwards(new_node->get_father());
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

void AVLTree::traverse_backwards(Node* node) {

    node->update_height();

    int diff = node->get_height_diff();

    if (diff < -1) { // left deeper
        int left_diff = node->get_left()->get_height_diff();

        if (left_diff < 0) {// left -> left case1 @ example
            printf("case1\n");
            Node* new_root = node->get_left();
            new_root->set_father(node->get_father());

            Node* temp = new_root->get_right();

            new_root->set_right(node);
            node->set_left(temp);
            node->update_height();
            node = new_root;
        } 
		else { // left -> right case3 @ example
			printf("case3\n");
            Node* new_root = node->get_left()->get_right();
            new_root->set_father(node->get_father());
            
            Node* temp_left = new_root->get_left();
            Node* temp_right = new_root->get_right();
            
            new_root->set_left(node->get_left());
            new_root->set_right(node);
            
            new_root->get_left()->set_right(temp_left);
            new_root->get_right()->set_left(temp_right);
            
            node->update_height();
            new_root->update_height();
            node = new_root;
		
        }
    }
    else if (diff > 1) { // right deeper
        
        int right_diff = node->get_right()->get_height_diff();
        
        if (right_diff < 0) { // right->left case4
            printf("case4\n");
            Node* new_root  = node->get_right()->get_left();
            new_root->set_father(node->get_father());
            
            Node* temp_left = new_root->get_left();
            Node* temp_right = new_root->get_right();
            
            new_root->set_left(node);
            new_root->set_right(node->get_right());
            
            new_root->get_left()->set_right(temp_left);
            new_root->get_right()->set_left(temp_right);
           
            node->update_height();
            new_root->update_height();
            node = new_root;
            
        }
        else { // right->right case2
            printf("case2\n");
            Node* new_root = node->get_right();
            new_root->set_father(node->get_father());
            
            Node* temp = new_root->get_left();
            
            new_root->set_left(node);
            node->set_right(temp);
            node->update_height();
            node = new_root;
            
        }
    }

    if (node->get_father() == NULL) {
        root = node;
        return;
    }

    traverse_backwards(node->get_father());
}

void AVLTree::iterate_tree() {
    Node* n = root;

    printf("l - left\n");
    printf("r - right\n");
    printf("f - father\n");
    printf("root - root\n");
    printf("quit - quit\n");

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
            return;
        } else
            printf("Unknown cmd\n");
    }
}

int main(int arc, char** argv) {
    //AVLTree *a = new AVLTree;
    AVLTree* t = new AVLTree();
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
    t->iterate_tree();
    return 0;
}
