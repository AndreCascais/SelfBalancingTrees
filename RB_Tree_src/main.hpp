#pragma once

// C++ Headers
#include <map>
#include <iostream>
#include <algorithm>
#include <chrono>

// C Headers
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>

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
    RBNode<K, V>* minimum_from(RBNode<K, V>* node);
    RBNode<K, V>* maximum_from(RBNode<K, V>* node);

    RBNode<K, V>* find_with_key(RBNode<K, V>* rootOfSubtree, K key);
    RBNode<K, V>* find_with_key(K key);

    void insert(K key, V value);
    void insert(RBNode<K, V>* rootOfSubtree, RBNode<K, V>* newNode);
    void insertFixUp(RBNode<K, V>* node_Z);

    bool remove(K key);
    void remove(RBNode<K, V>* node_Z);
    void removeFixUp(RBNode<K, V>* node_X);

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
    double get_ratio();
    int get_height(RBNode<K, V>* pNode);
};
