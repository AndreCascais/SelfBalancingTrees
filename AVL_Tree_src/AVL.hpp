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
class AVLNode {
public:
    explicit AVLNode(T v);
    ~AVLNode();

    int get_height();
    void update_height();
    int get_height_diff();
    T get_value();
    void set_left(AVLNode<T>* n);
    AVLNode<T>* get_left();
    void set_right(AVLNode<T>* n);
    AVLNode<T>* get_right();
    void set_father(AVLNode<T>* n);
    AVLNode<T>* get_father();
    void set_son(AVLNode<T>* n);
    void delete_son(AVLNode<T>* n);

    AVLNode<T>* get_min();
    AVLNode<T>* get_max();
    void print_node();

private:
    T height;
    T value;
    AVLNode<T>* left;
    AVLNode<T>* right;
    AVLNode<T>* father;
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
    AVLNode<T>* lookup(T v);
    double get_ratio();

private:
    void destroy_tree(AVLNode<T>* node);
    AVLNode<T>* find_value(AVLNode<T>* node, T v);
    void rotate_right(AVLNode<T>* node_x);
    void rotate_left(AVLNode<T>* node_x);
    AVLNode<T>* add_value(AVLNode<T>* node, T v);
    AVLNode<T>* remove_node(AVLNode<T>* node);
    void traverse_backwards(AVLNode<T>* node);
    int get_n_nodes(AVLNode<T>* node);
    int get_height(AVLNode<T>* node);

    AVLNode<T>* root;

    void print_help() const;
};
