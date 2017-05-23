#include <iostream>
#include <map>

#include <cstring>
#include <cstdio>
#include <cstdlib>

enum class Color {
    RED, BLACK
};

class RBNode {
public:
    RBNode();

    RBNode(int value);

    RBNode(int value, RBNode* leftChild, RBNode* rightChild, RBNode* parent);

    ~RBNode();

    int get_height();

    void set_height(int h);

    void update_height();

    int get_height_diff();

    int get_value();

    void set_left(RBNode* n);

    RBNode* get_left();

    void set_right(RBNode* n);

    RBNode* get_right();

    void set_father(RBNode* n);

    RBNode* get_father();

    RBNode* isRoot();

    void print_node();

private:
    Color _color_type;
    int _height;
    int _value;
    RBNode* _leftChild;
    RBNode* _rightChild;
    RBNode* _parent;
};

class RBTree {
public:
    RBTree();

    ~RBTree();

    void iterate_tree();

    void add_value(int n);

    void insert(RBNode* node, int n);

    void remove(RBNode* node);

private:
    RBNode* _root;
    int _size;
};

RBNode::RBNode(int key, RBNode* leftChild, RBNode* rightChild, RBNode* parent) {
    _color_type = Color::BLACK;
    _height = 0;
    _value = key;
    _leftChild = leftChild;
    _rightChild = rightChild;
    _parent = parent;
}

RBNode::RBNode(int v) {
    RBNode::RBNode(v, nullptr, nullptr, nullptr);
}

int RBNode::get_value() {
    return _value;
}

int RBNode::get_height() {
    return _height;
}

void RBNode::set_height(int h) {
    _height = h;
}

void RBNode::set_left(RBNode* n) {
    _leftChild = n;
}

RBNode* RBNode::get_left() {
    return _leftChild;
}

void RBNode::set_right(RBNode* n) {
    _rightChild = n;
}

RBNode* RBNode::get_right() {
    return _rightChild;
}

RBNode::RBNode() {
    _color_type = Color::BLACK;
}

RBNode::~RBNode() {

}

RBTree::RBTree() {
    _root = new RBNode();
}

void RBTree::add_value(int n) {
    if (_root == nullptr) {
        std::cout << "Creating root" << std::endl;
        _root = new RBNode(n);
    } else
        insert(_root, n);

}

void RBTree::insert(RBNode* node, int n) { // Assumir valores diferentes a serem inseridos
    int value = node->get_value();
    if (n > value) {// Right
        RBNode* node_right = node->get_right();
        if (node_right == NULL)
            node->set_right(new RBNode(n));
        else
            insert(node_right, n);
    } else { // Left
        RBNode* node_left = node->get_left();
        if (node_left == NULL)
            node->set_left(new RBNode(n));
        else
            insert(node_left, n);
    }

}

void RBTree::iterate_tree() {
    RBNode* n = _root;

    printf("l - left\n");
    printf("r - right\n");
    printf("root - root\n");
    printf("quit - quit\n");

    char s[10];
    while (true) {

        printf("I am at %d\n", n->get_value());
        scanf("%s", s);

        if (strcmp(s, "l") == 0) {
            RBNode* left = n->get_left();
            if (left == nullptr)
                printf("Not going to NULL RBNode\n");
            else
                n = left;
        } else if (strcmp(s, "r") == 0) {
            RBNode* right = n->get_right();
            if (right == nullptr)
                printf("Not going to NULL RBNode\n");
            else
                n = right;
        } else if (strcmp(s, "root") == 0) {
            n = _root;
        } else if (strcmp(s, "quit") == 0) {
            return;
        } else
            printf("Unknown cmd\n");
    }
}

void RBTree::remove(RBNode* node) {

}

int main(int arc, char** argv) {
    //RBTree *a = new RBTree;
    RBTree* t = new RBTree();
    t->add_value(1);
    t->add_value(2);
    t->iterate_tree();
    return 0;
}
