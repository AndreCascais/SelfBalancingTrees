#pragma once

// C++ Headers
#include <iostream>
#include <map>
#include <chrono>

// C Headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctgmath>

template<class T>
class SplayNode {
public:
    explicit SplayNode(T value);
    ~SplayNode();

    T get_value();
    void set_left(SplayNode<T>*);
    SplayNode<T>* get_left();
    void set_right(SplayNode<T>*);
    SplayNode<T>* get_right();
    void set_father(SplayNode<T>*);
    SplayNode<T>* get_father();
    void set_son(SplayNode<T>*);
    void delete_son(SplayNode<T>*);

    SplayNode<T>* get_min();
    SplayNode<T>* get_max();
    void print_node();

private:
    T value;
    SplayNode<T>* left;
    SplayNode<T>* right;
    SplayNode<T>* father;
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
    SplayNode<T>* lookup(T v);
    double get_ratio();

private:
    void destroy_tree(SplayNode<T>*);
    SplayNode<T>* find_value(SplayNode<T>*, T);
    void rotate_right(SplayNode<T>*);
    void rotate_left(SplayNode<T>*);
    SplayNode<T>* add_value(SplayNode<T>*, T);
    void remove_root();
    void splay(SplayNode<T>*);
    int get_n_nodes(SplayNode<T>*);
    int get_height(SplayNode<T>*);

    SplayNode<T>* root;
};