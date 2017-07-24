#pragma once

#include <iostream>
#include <string.h>
#include <map>
#include <tgmath.h>
#include <chrono>

#include <stdio.h>
#include <stdlib.h>

template<class T>
class Node {
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

template<class T>
class SplayTree {
public:
    SplayTree();
    ~SplayTree();
    void iterate_tree(FILE* file);
    void destroy_tree();
    void add_value(T);
    void remove_value(T v);
    Node<T>* lookup(T v);
    double get_ratio();

private:
    void destroy_tree(Node<T>*);
    void delete_node(Node<T>*);
    Node<T>* find_value(Node<T>*, T);
    void rotate_right(Node<T>*);
    void rotate_left(Node<T>*);
    Node<T>* add_value(Node<T>*, T);
    void remove_root();
    void splay(Node<T>*);
    int get_n_nodes(Node<T>*);
    int get_height(Node<T>*);

    Node<T>* root;
};