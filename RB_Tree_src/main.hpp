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

    int get_height();

    void set_height(int h);

    Color get_color();

    int get_value();

    void set_left(RBNode* n);

    RBNode<K, V>* get_left();

    void set_right(RBNode* n);

    RBNode<K, V>* get_right();

    void set_father(RBNode* n);

    RBNode<K, V>* get_father();

    RBNode<K, V>* isRoot();

    void print_node();

private:
    K _key;
    V _value;
    Color _color_type;
    RBNode<K, V>* _leftChild;
    RBNode<K, V>* _rightChild;
    RBNode<K, V>* _parent;
};


template<typename K, typename V>
class RBTree {
public:
    RBTree();

    ~RBTree();

    void iterate_tree(FILE* f);

    void add_value(K key, V value);

    void insert(RBNode<K, V>* node, int n);

    void remove(RBNode<K, V>* node);

    void remove_value(K key);

    void destroy_tree();

private:
    RBNode<K, V>* _root;
    int _size;

    void destroy_tree(RBNode<K, V>* node);
};


template<typename K, typename V>
void RBNode<K, V>::set_right(RBNode* n) {
    _rightChild = n;
}

template<typename K, typename V>
RBNode<K, V>* RBNode<K, V>::get_right() {
    return _rightChild;
}

template<typename K, typename V>
RBNode<K, V>::RBNode() {
    _leftChild = nullptr;
    _rightChild = nullptr;
    _parent = nullptr;
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
    _parent = parent;
}

template<typename K, typename V>
RBNode<K, V>::~RBNode() = default;



template<typename K, typename V>
RBNode<K, V>::RBNode(K key, V value) {
    RBNode<K, V>::RBNode(key, value, nullptr, nullptr, nullptr);
    _color_type = Color::BLACK;
}


template<typename K, typename V>
int RBNode<K, V>::get_value() {
    return _value;
}


template<typename K, typename V>
void RBNode<K, V>::set_left(RBNode* n) {
    _leftChild = n;
}

template<typename K, typename V>
RBNode<K, V>* RBNode<K, V>::get_left() {
    return _leftChild;
}

template<typename K, typename V>
RBNode<K, V>* RBNode<K, V>::get_father() {
    return _parent;
}

template<typename K, typename V>
void RBNode<K, V>::print_node() {
    // << " my height is " << this->get_color()
    std::cout << "I am at " << this->get_value()  << std::endl;
}

template<typename K, typename V>
Color RBNode<K,V>::get_color() {
    return _color_type;
}


template<typename K, typename V>
RBTree<K, V>::RBTree() {
    _root = new RBNode<K, V>();
}


template<typename K, typename V>
void RBTree<K, V>::add_value(K key, V value) {
    if (_root == nullptr) {
        std::cout << "Creating root" << std::endl;
        _root = new RBNode<K, V>(key, value);
    }
    else {
        insert(_root, value);
    }

}

template<typename K, typename V>
void RBTree<K, V>::remove(RBNode<K, V>* node) {

}


// FIX THIS!!!!!!!!!!!!!!!!!
template<typename K, typename V>
void RBTree<K, V>::insert(RBNode<K, V>* node, int n) { // Assumir valores diferentes a serem inseridos
    int value = node->get_value();
    if (n > value) {// Right
        RBNode<K, V>* node_right = node->get_right();
        if (node_right == nullptr) {
            node->set_right(new RBNode<K, V>(n, 0));
        }
        else {
            insert(node_right, n);
        }
    }
    else { // Left
        RBNode<K, V>* node_left = node->get_left();
        if (node_left == nullptr) {
            node->set_left(new RBNode<K, V>(n, 0));
        }
        else {
            insert(node_left, n);
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
                this->add_value(v, 0);
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
            RBNode<K, V>* left = n->get_left();
            if (left == NULL) {
                printf("Not going to NULL Node\n");
            }
            else {
                n = left;
            }
        }
        else if (strcmp(s, "r") == 0) {
            RBNode<K, V>* right = n->get_right();
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
            this->add_value(v, 0);
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
    if (node != NULL) {
        destroy_tree(node->get_left());
        destroy_tree(node->get_right());
        delete node;
    }
}

template<typename K, typename V>
RBTree<K, V>::~RBTree() = default;

template<typename K, typename V>
void RBTree<K, V>::remove_value(K key) {

}

