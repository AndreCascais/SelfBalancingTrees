#pragma once

// C++ Headers
#include <iostream>
#include <map>
#include <chrono>

// C Headers
#include <cstdio>
#include <cstdlib>
#include <ctgmath>
#include <cstring>

template<class T>
class Node {
public:
    Node(T v);
    ~Node();

    int get_height();
    void update_height();
    int get_height_diff();
    T get_value();
    void set_left(Node<T>* n);
    Node<T>* get_left();
    void set_right(Node<T>* n);
    Node<T>* get_right();
    void set_father(Node<T>* n);
    Node<T>* get_father();
    void set_son(Node<T>* n);
    void delete_son(Node<T>* n);

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

template<class T>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void iterate_tree(FILE* file);
    void destroy_tree();
    void add_value(T v);
    void remove_value(T v);
    Node<T>* lookup(T v);
    double get_ratio();

private:
    void destroy_tree(Node<T>* node);
    void delete_node(Node<T>*);
    Node<T>* find_value(Node<T>* node, T v);
    void rotate_right(Node<T>* node_x);
    void rotate_left(Node<T>* node_x);
    Node<T>* add_value(Node<T>* node, T v);
    Node<T>* remove_node(Node<T>* node);
    void traverse_backwards(Node<T>* node);
    int get_n_nodes(Node<T>* node);
    int get_height(Node<T>* node);

    Node<T>* root;
};
