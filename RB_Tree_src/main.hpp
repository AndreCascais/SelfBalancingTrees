#pragma once

#include <map>

#include <cstring>
#include <cstdio>
#include <cstdlib>

enum class Color {
    RED, BLACK
};

template<typename K, typename V>
class RBNode {
public:
    RBNode();

    RBNode(K key, V value);

    RBNode(K key, V value, RBNode* leftChild, RBNode* rightChild, RBNode* parent);

    ~RBNode();

    V get_value();

    K get_key();

    void set_color(Color c);

    Color get_color();

    RBNode<K, V>* get_leftChild();

    RBNode<K, V>* get_rightChild();

    void set_father(RBNode* n);

    void set_rightChild(RBNode* n);

    void set_leftChild(RBNode* n);

    RBNode<K, V>* get_father();

    void print_node();

    char color_to_string();

    bool isRightChild();

    bool isLeftChild();

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
    RBTree();

    ~RBTree();

    RBNode<K, V>* get_successorOf(RBNode<K, V>* node);

    RBNode<K, V>* minimumFrom(RBNode<K, V>* node);

    RBNode<K, V>* maximumFrom(RBNode<K, V>* node);

    void iterate_tree(FILE* f);

    void insert(K key, V value);

    void insert(RBNode<K, V>* rootOfSubtree, RBNode<K, V>* newNode);

    void insertFixUp(RBNode<K, V>* rootOfSubtree);

    void set_leftChild(RBNode<K, V>* parent, RBNode<K, V>* child);

    void set_rightChild(RBNode<K, V>* parent, RBNode<K, V>* child);

    void remove(RBNode<K, V>* node);

    void remove_value(K key);

    void destroy_tree();

private:
    RBNode<K, V>* _nullLeaf;

    RBNode<K, V>* _root;

    int _size;

    void destroy_tree(RBNode<K, V>* node);
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
RBNode<K, V>::~RBNode() = default;


template<typename K, typename V>
RBNode<K, V>::RBNode(K key, V value) : RBNode<K, V>::RBNode(key, value, nullptr, nullptr, nullptr) {};


template<typename K, typename V>
V RBNode<K, V>::get_value() {
    return _value;
}

template<typename K, typename V>
K RBNode<K, V>::get_key() {
    return _key;
}


template<typename K, typename V>
void RBTree<K, V>::set_leftChild(RBNode<K, V>* father, RBNode<K, V>* child) {
    father->set_leftChild(child);
    child->set_father(father);
    child->set_color(Color::RED);
    insertFixUp(child);
}


template<typename K, typename V>
void RBTree<K, V>::set_rightChild(RBNode<K, V>* father, RBNode<K, V>* child) {
    father->set_rightChild(child);
    child->set_father(father);
    child->set_color(Color::RED);
    insertFixUp(child);
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
    std::cout << "I am at key: " << this->get_key() << "with value" << this->get_value()
              << "my color is " << this->color_to_string() << std::endl;
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
char RBNode<K, V>::color_to_string() {
    switch (this->_color_type) {
        case Color::RED:
            return 'R';
        case Color::BLACK:
            return 'B';
    }
}


template<typename K, typename V>
RBNode<K, V>* RBTree<K, V>::minimumFrom(RBNode<K, V>* node) {
    auto leftChild = node->get_leftChild();
    if ( leftChild != nullptr) {
        if ( leftChild  == _nullLeaf ) {
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
        if ( rightChild == _nullLeaf ) {
            return node;
        }
        return maximumFrom(rightChild);
    }
    return nullptr;
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
RBTree<K, V>::RBTree() {
    _nullLeaf = new RBNode<K, V>();
    _root = _nullLeaf;
    _size = 0;
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
bool RBNode<K, V>::isRightChild() {
    if (this->get_father() == nullptr) {
        return false;
    }
    return (this->get_father()->get_rightChild() == this);
}


template<typename K, typename V>
bool RBNode<K, V>::isLeftChild() {
    if (this->get_father() == nullptr) {
        return false;
    }
    return (this->get_father()->get_leftChild() == this);
}


template<typename K, typename V>
void RBTree<K, V>::remove(RBNode<K, V>* node) {


    //Missing implementation
    _size-=1;
}


template<typename K, typename V>
void RBTree<K, V>::remove_value(K key) {




    //Missing implementation
}


template<typename K, typename V>
void RBTree<K, V>::insertFixUp(RBNode<K, V>* rootOfSubtree) {

}


template<typename K, typename V>
void RBTree<K, V>::insert(K key, V value) {

    auto newNode = new RBNode<K, V>(key, value);
    if (_root == _nullLeaf) {
        std::cout << "We have a root now!" << std::endl;
        _root = newNode;
    }
    else {
        insert(_root, newNode);
    }

    _size += 1;
}


// Assumir valores diferentes a serem inseridos
template<typename K, typename V>
void RBTree<K, V>::insert(RBNode<K, V>* rootOfSubtree, RBNode<K, V>* newNode) {
    V newValue = newNode->get_value();
    K newKey = newNode->get_key();
    V oldValue = rootOfSubtree->get_value();
    K oldKey = rootOfSubtree->get_key();

    if (newValue > oldValue) { // Insert on the right
        auto rightNode = rootOfSubtree->get_rightChild();
        if (rightNode == _nullLeaf) {
            set_rightChild(rootOfSubtree, newNode);
        }
        else {
            insert(rightNode, newNode);
        }
    }
    else { // Insert on the left
        auto leftNode = rootOfSubtree->get_leftChild();
        if (leftNode == _nullLeaf) {
            set_leftChild(rootOfSubtree, newNode);
        }
        else {
            insert(leftNode, newNode);
        }
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
    if (file != NULL) {
        while (true) {
            fscanf(file, "%s", s);
            if (strcmp(s, "add") == 0) {
                int v;
                fscanf(file, "%d", &v);
                this->insert(v, 0);
            }
            else if (strcmp(s, "remove") == 0) {
                int v;
                fscanf(file, "%d", &v);
                this->remove_value(v);
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
            int v;
            scanf("%d", &v);
            this->remove_value(v);
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
RBTree<K, V>::~RBTree() {

}




