#include "RB.hpp"

template<typename K, typename V>
RBNode<K, V>::RBNode() {
    _leftChild = nullptr;
    _rightChild = nullptr;
    _father = nullptr;
    _key = nullptr;
    _value = nullptr;
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
        std::cout << "This can't happen ---- brother" << std::endl;
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
RBNode<K, V>* RBTree<K, V>::minimum_from(RBNode<K, V>* node) {
    auto leftChild = node->get_leftChild();
    if (leftChild != nullptr) {
        if (leftChild == _nullLeaf) {
            return node;
        }
        return minimum_from(leftChild);
    }
    return nullptr;
}


template<typename K, typename V>
RBNode<K, V>* RBTree<K, V>::maximum_from(RBNode<K, V>* node) {
    auto rightChild = node->get_rightChild();
    if (rightChild != nullptr) {
        if (rightChild == _nullLeaf) {
            return node;
        }
        return maximum_from(rightChild);
    }
    return nullptr;
}


template<typename K, typename V>
RBNode<K, V>* RBTree<K, V>::get_successorOf(RBNode<K, V>* node) {
    // If node has right child, then the successor is the min of the right subtree
    auto rightChild = node->get_rightChild();
    if (rightChild != nullptr) {
        if (rightChild != _nullLeaf) {
            return minimum_from(rightChild);
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
void RBTree<K, V>::remove(RBNode<K, V>* node_Z) {


    auto node_Y = node_Z;
    RBNode<K, V>* node_X;

    Color y_original_color = node_Y->get_color();

    if (node_Z->get_leftChild() == _nullLeaf) { // leftChild is a nullLeaf, rightChild may or may not be a nullLeaf
        node_X = node_Z->get_rightChild();
        transplant(node_Z, node_Z->get_rightChild());
    }
    else if (node_Z->get_rightChild() == _nullLeaf) { // rightChild is a nullLeaf but leftChild isn't
        node_X = node_Z->get_leftChild();
        transplant(node_Z, node_Z->get_leftChild());
    }
    else { // neither child is a nullLeaf
        node_Y = get_successorOf(node_Z);
        y_original_color = node_Y->get_color();
        node_X = node_Y->get_rightChild();

        if (node_Y->get_father() == node_Z) {
            node_X->set_father(node_Y);
        }
        else {
            transplant(node_Y, node_Y->get_rightChild());
            node_Y->set_rightChild(node_Z->get_rightChild());
            node_Y->get_rightChild()->set_father(node_Y);
        }

        transplant(node_Z, node_Y);

        node_Y->set_leftChild(node_Z->get_leftChild());
        node_Y->get_leftChild()->set_father(node_Y);
        node_Y->set_color(node_Z->get_color());
    }


    if (y_original_color == Color::BLACK) {
        removeFixUp(node_X);
    }

}


template<typename K, typename V>
bool RBTree<K, V>::remove(K key) {

    RBNode<K, V>* node_to_remove = find_with_key(key);

    if (node_to_remove != _nullLeaf) {
        remove(node_to_remove);
        _size -= 1;
        return true;
    }
    return false;

}


template<typename K, typename V>
void RBTree<K, V>::removeFixUp(RBNode<K, V>* node_X) {

    if (node_X == _root || node_X->get_color() != Color::BLACK) {
        node_X->set_color(Color::BLACK);
        return;
    }

    auto node_W = node_X->get_brother();
    auto father = node_X->get_father();

    // Case 1: Brother is RED
    if (node_W->get_color() == Color::RED) {

        // Recolor brother and father
        node_W->set_color(Color::BLACK);
        father->set_color(Color::RED);

        if (node_X->isLeftChild()) {
            rotate_left(father);
            node_W = node_X->get_father()->get_rightChild();
        }
        else if (node_X->isRightChild()) {
            rotate_right(father);
            node_W = node_X->get_father()->get_leftChild();
        }
        else {
            std::cout << "WTFFF" << std::endl;
        }

    }

    // Case 2: Brother is BLACK and has two BLACK children
    if (node_W->get_leftChild()->get_color() == Color::BLACK && node_W->get_rightChild()->get_color() == Color::BLACK) {
        // Recolor brother and start again from node X's father
        node_W->set_color(Color::RED);
        removeFixUp(father);
    }

        // Case 3: Brother is BLACK with only one BLACK child
    else {

        // NodeX is right Child and BLACK child of brother is on the left
        if (node_X->isRightChild() && node_W->get_leftChild()->get_color() == Color::BLACK) {

            node_W->get_rightChild()->set_color(Color::BLACK);
            node_W->set_color(Color::RED);
            rotate_left(node_W);
            node_W = node_X->get_father()->get_leftChild();

        }

            // NodeX is left Child and BLACK child of brother is on the right
        else if (node_X->isLeftChild() && node_W->get_rightChild()->get_color() == Color::BLACK) {

            node_W->get_leftChild()->set_color(Color::BLACK);
            node_W->set_color(Color::RED);
            rotate_right(node_W);
            node_W = node_X->get_father()->get_rightChild();

        }

        // Case 4: Not sure??

        auto father = node_X->get_father();

        node_W->set_color(father->get_color());
        father->set_color(Color::BLACK);

        if (node_X->isLeftChild()) {
            node_W->get_rightChild()->set_color(Color::BLACK);
            rotate_left(father);
        }
        else if (node_X->isRightChild()) {
            node_W->get_leftChild()->set_color(Color::BLACK);
            rotate_right(father);
        }


        removeFixUp(_root);

    }

}


template<typename K, typename V>
RBNode<K, V>* RBTree<K, V>::find_with_key(RBNode<K, V>* rootOfSubtree, K key) {

    K keyOfRoot = rootOfSubtree->get_key();

    if (rootOfSubtree != _nullLeaf) {
        if (key == keyOfRoot) {
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

    RBNode<K, V>* father = node_Z->get_father();

    // We only need to fix the tree if the parent was also red
    if (father->get_color() != Color::RED) {
        return;
    }

    RBNode<K, V>* nodeY = node_Z->get_uncle();
    RBNode<K, V>* grandFather = node_Z->get_grandFather();

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
        else if (new_Z->isRightChild()) {
            rotate_left(newZ_grandFather);
        }
        else {
            std::cout << "WTFFF" << std::endl;
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
    newNode->set_father(_nullLeaf);
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
            rootOfSubtree->set_rightChild(newNode);
            newNode->set_father(rootOfSubtree);
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
            rootOfSubtree->set_leftChild(newNode);
            newNode->set_father(rootOfSubtree);
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

    int option = 1;
    int number;

    if (file != nullptr) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

//        double min_ratio = 100000;
//        double max_ratio = 0;
//        double avg_ratio = 0;

        int n_inserts, n_removes, n_lookups;
        fscanf(file, "%d%d%d%d", &option, &n_inserts, &n_removes, &n_lookups);
        for (int i = 0; i < n_inserts; i++) {
            fscanf(file, "%d", &number);
            K k = (K) malloc(sizeof(K));
            *k = number;
            V v = (V) malloc(sizeof(V));
            insert(k, v);
            free(k);
            free(v);

//            if (i % 1000 == 0) {
//                std::cout << i << std::endl;
//                bool result = verify();
//                if (!result) {
//                    std::cout << "some property failed" << std::endl;
//                }
//            }

//            if (i > 3) {
//                double ratio = get_ratio();
//                min_ratio = std::min(ratio, min_ratio);
//                max_ratio = std::max(ratio, max_ratio);
//                avg_ratio += ratio;
//            }
        }

//        avg_ratio = avg_ratio / (n_inserts - 4);
//        printf("min ratio = %lf, max_ratio = %lf, avg_ratio = %lf\n", min_ratio, max_ratio, avg_ratio);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time for inserts: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds"
                  << std::endl;
        begin = std::chrono::steady_clock::now();

        for (int i = 0; i < n_removes; i++) {
            fscanf(file, "%d", &number);
            K k = (K) malloc(sizeof(K));
            *k = number;
            remove(k);
            free(k);

//            if (i % 1000 == 0) {
//                std::cout << i << std::endl;
//                bool result = verify();
//                if (!result) {
//                    std::cout << "some property failed" << std::endl;
//                }
//            }
        }

        end = std::chrono::steady_clock::now();
        std::cout << "Time for removals: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds"
                  << std::endl;
        begin = std::chrono::steady_clock::now();

        for (int i = 0; i < n_lookups; i++) {
            fscanf(file, "%d", &number);
            K k = (K) malloc(sizeof(K));
            *k = number;
            find_with_key(k);
//            if (i % 1000 == 0) {
//                std::cout << i << std::endl;
//                bool result = verify();
//                if (!result) {
//                    std::cout << "some property failed" << std::endl;
//                }
//            }
        }
        end = std::chrono::steady_clock::now();
        std::cout << "Time for lookups: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds"
                  << std::endl;
    }

    if (option == 0) {
        destroy_tree();
        return;
    }

    char help_str[] = "Done reading from file\n"
            "l - left\n"
            "r - right\n"
            "f - father\n"
            "t - root\n"
            "q - quit\n"
            "a v  - adds value v to tree\n"
            "d v - deletes value v from tree\n";

    printf("%s", help_str);
    char cmd;

    RBNode<K, V>* n = _root;
    while (true) {

        if (n != _nullLeaf) {
            n->print_node();

            bool result = verify();
            if (!result) {
                std::cout << "some property failed" << std::endl;
            }
        }
        scanf("\n%c", &cmd);
        switch (cmd) {
            case 'l' : {
                RBNode<K, V>* left = n->get_leftChild();
                if (left == _nullLeaf) {
                    printf("Not going to _nullLeaf\n");
                }
                else {
                    n = left;
                }
            }
                break;
            case 'r' : {
                RBNode<K, V>* right = n->get_rightChild();
                if (right == _nullLeaf) {
                    printf("Not going to _nullLeaf\n");
                }
                else {
                    n = right;
                }
            }
                break;
            case 't' : {
                if (n == _root) {
                    printf("Already at root\n");
                }
                else {
                    n = n->get_father();
                }
            }
                break;
            case 'q' :
                destroy_tree();
                return;

            case 'a' : {
                scanf("%d", &number);
                K k = (K) malloc(sizeof(K));
                *k = number;
                V v = (V) malloc(sizeof(V));
                insert(k, v);
                n = _root;

            }
                break;
            case 'd' : {
                scanf("%d", &number);
                K k = (K) malloc(sizeof(K));
                *k = number;
                remove(k);
                free(k);
                n = _root;

            }
                break;
            default :
                std::cout << "Unknown cmd\n" << std::endl;
        }
    }
}


template<typename K, typename V>
void RBTree<K, V>::destroy_tree() {
    destroy_tree(_root);
    delete _nullLeaf;
}


template<typename K, typename V>
void RBTree<K, V>::destroy_tree(RBNode<K, V>* node) {
    if (node != _nullLeaf) {
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

    if (n == _nullLeaf) {
        return true;
    }

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


template<typename K, typename V>
double RBTree<K, V>::get_ratio() {
    int n_nodes = _size;
    int height = get_height(_root);
    return height / (log(n_nodes) / (log(2)));

}


template<typename K, typename V>
int RBTree<K, V>::get_height(RBNode<K, V>* n) {
    return (n == _nullLeaf) ? 0 : 1 + std::max(get_height(n->get_leftChild()), get_height(n->get_rightChild()));
}
