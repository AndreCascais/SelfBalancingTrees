#pragma once

// C++ Headers
#include <map>
#include <iostream>
#include <algorithm>

// C Headers
#include <cstring>
#include <cstdio>
#include <cstdlib>

enum class Color {
    RED, BLACK
};

template<typename K, typename V>
class RBNode {
public:
    // Constructors & Destructors
    RBNode();
    RBNode(K key, V value);
    RBNode(K key, V value, RBNode* leftChild, RBNode* rightChild, RBNode* parent);

    ~RBNode();

    // Getters & Setters
    V get_value();
    K get_key();
    Color get_color();
    RBNode<K, V>* get_leftChild();
    RBNode<K, V>* get_rightChild();
    RBNode<K, V>* get_father();

    void set_rightChild(RBNode* n);
    void set_leftChild(RBNode* n);
    void set_father(RBNode* n);
    void set_color(Color c);


    // Auxiliary Stuff
    void print_node();
    char color_to_char();

    bool isRightChild();
    bool isLeftChild();

    RBNode<K, V>* get_brother();
    RBNode<K, V>* get_uncle();
    RBNode<K, V>* get_grandFather();

private:
    K _key;
    V _value;
    Color _color_type;
    RBNode<K, V>* _leftChild;
    RBNode<K, V>* _rightChild;
    RBNode<K, V>* _father;
};


template<typename K, typename V>
class RBTree {
public:
    // Constructors & Destructors
    RBTree();

    ~RBTree();

    // Auxiliary Stuff
    RBNode<K, V>* get_successorOf(RBNode<K, V>* node);
    RBNode<K, V>* minimumFrom(RBNode<K, V>* node);
    RBNode<K, V>* maximumFrom(RBNode<K, V>* node);

    RBNode<K, V>* find_with_key(RBNode<K, V>* rootOfSubtree, K key);
    RBNode<K, V>* find_with_key(K key);

    void set_leftChild_updateFather(RBNode<K, V>* father, RBNode<K, V>* child);
    void set_rightChild_updateFather(RBNode<K, V>* father, RBNode<K, V>* child);

    void insert(K key, V value);
    void insert(RBNode<K, V>* rootOfSubtree, RBNode<K, V>* newNode);
    void insertFixUp(RBNode<K, V>* node_Z);

    bool remove(K key);
    void remove(RBNode<K, V>* rootOfSubtree, RBNode<K, V>* newNode);
    void removeFixUp(RBNode<K, V>* node_Z);

    void rotate_left(RBNode<K, V>* nodeX);
    void rotate_right(RBNode<K, V>* nodeX);
    void transplant(RBNode<K, V>* node_U, RBNode<K, V>* node_V);


    void iterate_tree(FILE* f);
    void destroy_tree();


    bool property2();
    bool property4(RBNode<K, V>* n);
    bool property5(RBNode<K, V>* n);
    bool verify();

private:
    RBNode<K, V>* _nullLeaf;

    RBNode<K, V>* _root;

    int _size;

    void destroy_tree(RBNode<K, V>* node);
    int black_height(RBNode<K, V>* n);
};


template<typename K, typename V>
RBNode<K, V>::RBNode() {
    _leftChild = nullptr;
    _rightChild = nullptr;
    _father = nullptr;
//    _key = nullptr;
//    _value = nullptr;
    _color_type = Color::BLACK;
}


template<typename K, typename V>
RBNode<K, V>::RBNode(K key, V value, RBNode* leftChild, RBNode* rightChild, RBNode* parent) {
    _color_type = Color::BLACK;
    _key = key;
    _value = value;
    _leftChild = leftChild;
    _rightChild = rightChild;
    _father = parent;
}


template<typename K, typename V>
RBNode<K, V>::RBNode(K key, V value) : RBNode<K, V>::RBNode(key, value, nullptr, nullptr, nullptr) {};


template<typename K, typename V>
RBNode<K, V>::~RBNode() = default;


template<typename K, typename V>
V RBNode<K, V>::get_value() {
    return _value;
}


template<typename K, typename V>
K RBNode<K, V>::get_key() {
    return _key;
}


template<typename K, typename V>
RBNode<K, V>* RBNode<K, V>::get_leftChild() {
    return _leftChild;
}


template<typename K, typename V>
RBNode<K, V>* RBNode<K, V>::get_rightChild() {
    return _rightChild;
}


template<typename K, typename V>
RBNode<K, V>* RBNode<K, V>::get_father() {
    return _father;
}


template<typename K, typename V>
void RBNode<K, V>::print_node() {
    std::cout << "I am at key: " << this->get_key() << " || with value: " << this->get_value()
              << " || my color is: " << this->color_to_char() << std::endl;
}


template<typename K, typename V>
Color RBNode<K, V>::get_color() {
    return _color_type;
}


template<typename K, typename V>
void RBNode<K, V>::set_color(Color c) {
    this->_color_type = c;
}


template<typename K, typename V>
char RBNode<K, V>::color_to_char() {
    switch (this->_color_type) {
        case Color::RED:
            return 'R';
        case Color::BLACK:
            return 'B';
    }
}


template<typename K, typename V>
void RBNode<K, V>::set_father(RBNode* n) {
    _father = n;
}


template<typename K, typename V>
void RBNode<K, V>::set_leftChild(RBNode* n) {
    _leftChild = n;
}


template<typename K, typename V>
void RBNode<K, V>::set_rightChild(RBNode* n) {
    _rightChild = n;
}


template<typename K, typename V>
bool RBNode<K, V>::isRightChild() {
    return this->get_father() != nullptr && this->get_father()->get_rightChild() == this;
}


template<typename K, typename V>
bool RBNode<K, V>::isLeftChild() {
    return this->get_father() != nullptr && this->get_father()->get_leftChild() == this;
}


template<typename K, typename V>
RBNode<K, V>* RBNode<K, V>::get_brother() {
    if (isLeftChild()) {
        return get_father()->get_rightChild();
    }
    else if (isRightChild()) {
        return get_father()->get_leftChild();
    }
    else {
        std::cout << "This can't happen";
        return nullptr;
    }
}


template<typename K, typename V>
RBNode<K, V>* RBNode<K, V>::get_uncle() {
    return get_father()->get_brother();
}


template<typename K, typename V>
RBNode<K, V>* RBNode<K, V>::get_grandFather() {
    return get_father()->get_father();
}


template<typename K, typename V>
RBTree<K, V>::RBTree() {
    _nullLeaf = new RBNode<K, V>();
    _root = _nullLeaf;
    _root->set_father(_nullLeaf);
    _size = 0;
}


template<typename K, typename V>
RBTree<K, V>::~RBTree() = default;


template<typename K, typename V>
RBNode<K, V>* RBTree<K, V>::minimumFrom(RBNode<K, V>* node) {
    auto leftChild = node->get_leftChild();
    if (leftChild != nullptr) {
        if (leftChild == _nullLeaf) {
            return node;
        }
        return minimumFrom(leftChild);
    }
    return nullptr;
}


template<typename K, typename V>
RBNode<K, V>* RBTree<K, V>::maximumFrom(RBNode<K, V>* node) {
    auto rightChild = node->get_rightChild();
    if (rightChild != nullptr) {
        if (rightChild == _nullLeaf) {
            return node;
        }
        return maximumFrom(rightChild);
    }
    return nullptr;
}


template<typename K, typename V>
RBNode<K, V>* RBTree<K, V>::get_successorOf(RBNode<K, V>* node) {
    // If node has right child, then the successor is the min of the right subtree
    auto rightChild = node->get_rightChild();
    if (rightChild != nullptr) {
        if (rightChild != _nullLeaf) {
            return minimumFrom(rightChild);
        }
    }

    // Else go upwards until we find a node that is a left child, it's parent will be the successor
    auto currentNode = node;
    while (currentNode->isRightChild()) {
        currentNode = currentNode->get_father();
    }
    return currentNode->get_father();
}


template<typename K, typename V>
void RBTree<K, V>::set_leftChild_updateFather(RBNode<K, V>* father, RBNode<K, V>* child) {
    father->set_leftChild(child);
    child->set_father(father);
}


template<typename K, typename V>
void RBTree<K, V>::set_rightChild_updateFather(RBNode<K, V>* father, RBNode<K, V>* child) {
    father->set_rightChild(child);
    child->set_father(father);
}


template<typename K, typename V>
void RBTree<K, V>::remove(RBNode<K, V>* rootOfSubtree, RBNode<K, V>* newNode) {


}


template<typename K, typename V>
bool RBTree<K, V>::remove(K key) {

    RBNode<K, V>* node_to_remove = find_with_key(key);

    if (node_to_remove != _nullLeaf) {
        remove(_root, node_to_remove);
        _size -= 1;
        return true;
    }
    return false;

}


template<typename K, typename V>
void RBTree<K, V>::removeFixUp(RBNode<K, V>* node_Z) {

}


template<typename K, typename V>
RBNode<K, V>* RBTree<K, V>::find_with_key(RBNode<K, V>* rootOfSubtree, K key) {

    K keyOfRoot = rootOfSubtree->get_key();

    if (rootOfSubtree != _nullLeaf) {
        if (key == keyOfRoot){
            return rootOfSubtree;
        }
        if (key < keyOfRoot) {
            return find_with_key(rootOfSubtree->get_leftChild(), key);
        }
        else {
            return find_with_key(rootOfSubtree->get_rightChild(), key);
        }
    }

    return rootOfSubtree;
}


template<typename K, typename V>
RBNode<K, V>* RBTree<K, V>::find_with_key(K key) {
    return find_with_key(_root, key);
}


template<typename K, typename V>
void RBTree<K, V>::insertFixUp(RBNode<K, V>* node_Z) {

    RBNode<K, V>* nodeY = node_Z->get_uncle();
    RBNode<K, V>* father = node_Z->get_father();
    RBNode<K, V>* grandFather = node_Z->get_grandFather();

    // We only need to fix the tree if the parent was also red
    if (father->get_color() != Color::RED) {
        return;
    }

    // Case 1: Uncle is RED - recolor father and uncle and move z pointer to grandFather and start again.
    if (nodeY->get_color() == Color::RED) {
        father->set_color(Color::BLACK);
        nodeY->set_color(Color::BLACK);
        grandFather->set_color(Color::RED);

        insertFixUp(grandFather);
    }

        // Case 2: Uncle is BLACK
    else {
        auto new_Z = father; // keep pointer to father, since father will change to a different place after rotation

        if (father->isLeftChild() && node_Z->isRightChild()) { // left - right case
            rotate_left(father);
        }
        else if (father->isRightChild() && node_Z->isLeftChild()) { // right - left case
            rotate_right(father);
        }
        else { // left - left and right - right case
            new_Z = node_Z; // We don't actually need to change the z pointer to the father in this case, since no rotation happened
        }

        // Case 3: Starts here

        auto newZ_father = new_Z->get_father();
        auto newZ_grandFather = new_Z->get_grandFather();

        newZ_father->set_color(Color::BLACK);
        newZ_grandFather->set_color(Color::RED);

        if (new_Z->isLeftChild()) {
            rotate_right(newZ_grandFather);
        }
        else {
            rotate_left(newZ_grandFather);
        }

    }

    // Root might have become RED, must go back to BLACK
    _root->set_color(Color::BLACK);

}


template<typename K, typename V>
void RBTree<K, V>::insert(K key, V value) {

    auto newNode = new RBNode<K, V>(key, value);

    //tmp hack
    newNode->set_leftChild(_nullLeaf);
    newNode->set_rightChild(_nullLeaf);
    //tmp hack

    if (_root == _nullLeaf) {
        std::cout << "We have a root now!" << std::endl;
        _root = newNode;
    }
    else {
        insert(_root, newNode);
    }

    _size += 1;
}


template<typename K, typename V>
void RBTree<K, V>::insert(RBNode<K, V>* rootOfSubtree, RBNode<K, V>* newNode) {
    V newValue = newNode->get_value();
    K newKey = newNode->get_key();
    V oldValue = rootOfSubtree->get_value();
    K oldKey = rootOfSubtree->get_key();

    if (newKey > oldKey) { // Insert on the right
        auto rightNode = rootOfSubtree->get_rightChild();
        if (rightNode == _nullLeaf) {
            set_rightChild_updateFather(rootOfSubtree, newNode);
            newNode->set_color(Color::RED);
            insertFixUp(newNode);
        }
        else {
            insert(rightNode, newNode);
        }
    }
    else if (newKey < oldKey) { // Insert on the left
        auto leftNode = rootOfSubtree->get_leftChild();
        if (leftNode == _nullLeaf) {
            set_leftChild_updateFather(rootOfSubtree, newNode);
            newNode->set_color(Color::RED);
            insertFixUp(newNode);
        }
        else {
            insert(leftNode, newNode);
        }
    }
    else {
        std::cout << "For now assuming you can't add nodes with the same key" << std::endl;
    }

}


template<typename K, typename V>
void RBTree<K, V>::iterate_tree(FILE* file) {

    printf("l - left\n");
    printf("r - right\n");
    printf("f - father\n");
    printf("root - root\n");
    printf("quit - quit\n");
    printf("add - quit\n");
    printf("remove - quit\n");


    char s[10];
    if (file != nullptr) {
        while (true) {
            fscanf(file, "%s", s);
            if (strcmp(s, "add") == 0) {
                int k;
                fscanf(file, "%d", &k);
                this->insert(k, 0);
            }
            else if (strcmp(s, "remove") == 0) {
                int k;
                fscanf(file, "%d", &k);
                this->remove(k);
            }
            else if (strcmp(s, "end") == 0) {
                break;
            }
        }
    }
    printf("Done reading from file\n");
    RBNode<K, V>* n = _root;
    while (true) {

        if (n != NULL) {
            n->print_node();
        }
        scanf("%s", s);

        if (strcmp(s, "l") == 0) {
            RBNode<K, V>* left = n->get_leftChild();
            if (left == NULL) {
                printf("Not going to NULL Node\n");
            }
            else {
                n = left;
            }
        }
        else if (strcmp(s, "r") == 0) {
            RBNode<K, V>* right = n->get_rightChild();
            if (right == NULL) {
                printf("Not going to NULL Node\n");
            }
            else {
                n = right;
            }
        }
        else if (strcmp(s, "f") == 0) {
            if (n == _root) {
                printf("Already at root\n");
            }
            else {
                n = n->get_father();
            }
        }
        else if (strcmp(s, "root") == 0) {
            n = _root;
        }
        else if (strcmp(s, "quit") == 0) {
            this->destroy_tree();
            return;
        }
        else if (strcmp(s, "add") == 0) {
            int v;
            scanf("%d", &v);
            this->insert(v, 0);
            n = _root;
        }
        else if (strcmp(s, "remove") == 0) {
            int k;
            scanf("%d", &k);
            this->remove(k);
            n = _root;
        }
        else {
            printf("Unknown cmd\n");
        }
    }
}


template<typename K, typename V>
void RBTree<K, V>::destroy_tree() {
    destroy_tree(_root);
}


template<typename K, typename V>
void RBTree<K, V>::destroy_tree(RBNode<K, V>* node) {
    if (node != nullptr) {
        destroy_tree(node->get_leftChild());
        destroy_tree(node->get_rightChild());
        delete node;
    }
}


template<typename K, typename V>
void RBTree<K, V>::rotate_left(RBNode<K, V>* nodeX) {

    RBNode<K, V>* nodeY;

    nodeY = nodeX->get_rightChild();
    nodeX->set_rightChild(nodeY->get_leftChild());

    if (nodeX->get_rightChild() != _nullLeaf) {
        nodeX->get_rightChild()->set_father(nodeX);
    }

    nodeY->set_father(nodeX->get_father());

    if (nodeX->get_father() == _nullLeaf) { // if nodeX was the root
        _root = nodeY;
    }
    else if (nodeX->isLeftChild()) {
        nodeX->get_father()->set_leftChild(nodeY);
    }
    else if (nodeX->isRightChild()) {
        nodeX->get_father()->set_rightChild(nodeY);
    }
    else {
        std::cout << "this can't happen ----> rotate_left" << std::endl;
    }

    nodeY->set_leftChild(nodeX);
    nodeX->set_father(nodeY);

}


template<typename K, typename V>
void RBTree<K, V>::rotate_right(RBNode<K, V>* nodeX) {

    RBNode<K, V>* nodeY;

    nodeY = nodeX->get_leftChild();
    nodeX->set_leftChild(nodeY->get_rightChild());

    if (nodeX->get_leftChild() != _nullLeaf) {
        nodeX->get_leftChild()->set_father(nodeX);
    }

    nodeY->set_father(nodeX->get_father());

    if (nodeX->get_father() == _nullLeaf) { // if nodeX was the root
        _root = nodeY;
    }
    else if (nodeX->isLeftChild()) {
        nodeX->get_father()->set_leftChild(nodeY);
    }
    else if (nodeX->isRightChild()) {
        nodeX->get_father()->set_rightChild(nodeY);
    }
    else {
        std::cout << "this can't happen ----> rotate_right" << std::endl;
    }

    nodeY->set_rightChild(nodeX);
    nodeX->set_father(nodeY);

}


template<typename K, typename V>
void RBTree<K, V>::transplant(RBNode<K, V>* node_U, RBNode<K, V>* node_V) {

    auto node_U_father = node_U->get_father();

    if (node_U_father == _nullLeaf) { // if nodeU didn't have a father, then nodeU was the root
        _root = node_V;
    }
    else if (node_U->isLeftChild()) {
        node_U_father->set_leftChild(node_V);
    }
    else if (node_U->isRightChild()) {
        node_U_father->set_rightChild(node_V);
    }
    else {
        std::cout << "this can't happen ----> transplant" << std::endl;
    }

    // node_v's new father will now be node_U's father
    node_V->set_father(node_U_father);

}

template<typename K, typename V>
bool RBTree<K, V>::verify() {

    // Property 1. Every node is either red or black.
    // Guaranteed by using enum class Color

    // Property 2. The root is black.
    if (!property2()) {
        std::cout << " !!Violated-Property-1!! : root is red";
        return false;
    };

    // Property 3. Every leaf (NIL) is black.
    // Guaranteed by using nullLeaf to represent leaves.

    // Property 4. If a node is red, then both its children are black.
    if (!property4(_root)) {
        std::cout << " !!Violated-Property-4!!";
        return false;
    };

    // Property 5. For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.
    if (!property5(_root)) {
        std::cout << " !!Violated-Property-5!!";
        return false;
    };

    return true;
}


template<typename K, typename V>
bool RBTree<K, V>::property2() {
    return (_root->get_color() == Color::BLACK);
};


template<typename K, typename V>
bool RBTree<K, V>::property4(RBNode<K, V>* n) {
    if (n == _nullLeaf) {
        return true;
    }

    auto leftChild = n->get_leftChild();
    auto rightChild = n->get_rightChild();

    if (n->get_color() == Color::RED) {
        if (leftChild->get_color() == Color::RED) {
            return false;
        }
        if (rightChild->get_color() == Color::RED) {
            return false;
        }
    }

    return property4(leftChild) && property4(rightChild);

};


template<typename K, typename V>
bool RBTree<K, V>::property5(RBNode<K, V>* n) {

    auto left_child = n->get_leftChild();
    auto right_child = n->get_rightChild();
    int lH = black_height(left_child);
    int rH = black_height(right_child);

    if (lH != rH) {
        return false;
    }

    return property5(left_child) && property5(right_child);

};


template<typename K, typename V>
int RBTree<K, V>::black_height(RBNode<K, V>* n) {

    if (n == _nullLeaf) {
        return 0;
    }

    bool is_n_black = (n->get_color() == Color::BLACK);
    int height = is_n_black ? 1 : 0;
    return height + std::max(black_height(n->get_leftChild()), black_height(n->get_rightChild()));

};

