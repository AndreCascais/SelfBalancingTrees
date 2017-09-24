#include "AVL.hpp"

//@todo overload operador == entre nodes ?

template<class T>
AVLNode<T>::AVLNode(T v) {
    value = v;
    height = 0;
    left = nullptr;
    right = nullptr;
    father = nullptr;
}

template<class T>
AVLNode<T>::~AVLNode() = default;

template<class T>
T AVLNode<T>::get_value() {
    return value;
}

template<class T>
int AVLNode<T>::get_height() {
    return height;
}

template<class T>
void AVLNode<T>::update_height() {
    AVLNode<T>* left = this->get_left();
    AVLNode<T>* right = this->get_right();
    int height_left = (left == nullptr ? -1 : left->get_height());
    int height_right = (right == nullptr ? -1 : right->get_height());
    height = 1 + std::max(height_left, height_right);
}

template<class T>
int AVLNode<T>::get_height_diff() {
    AVLNode<T>* left = this->get_left();
    AVLNode<T>* right = this->get_right();
    int left_height = (left == nullptr ? -1 : left->get_height());
    int right_height = (right == nullptr ? -1 : right->get_height());

    return right_height - left_height;
}

template<class T>
void AVLNode<T>::set_left(AVLNode<T>* n) {
    if (n != nullptr) {
        n->set_father(this);
    }
    left = n;
}

template<class T>
AVLNode<T>* AVLNode<T>::get_left() {
    return left;
}

template<class T>
void AVLNode<T>::set_right(AVLNode<T>* n) {
    if (n != nullptr) {
        n->set_father(this);
    }
    right = n;
}

template<class T>
AVLNode<T>* AVLNode<T>::get_right() {
    return right;
}

template<class T>
void AVLNode<T>::set_father(AVLNode<T>* n) {
    father = n;
}

template<class T>
AVLNode<T>* AVLNode<T>::get_father() {
    return father;
}

template<class T>
void AVLNode<T>::set_son(AVLNode<T>* n) {
    if (n != nullptr) { // Have to also update either left or right
        T val = n->get_value();
        if (val > this->value) { //right
            this->set_right(n);
        }
        else { //left
            this->set_left(n);
        }
    }
    else { // only gets here when we want to set right to null
        this->set_right(nullptr); //@todo hack much ?
    }
}

template<class T>
void AVLNode<T>::delete_son(AVLNode<T>* n) { // deletes link only
    AVLNode<T>* left_node = n->get_left();
    if (left_node != nullptr && left_node->get_value() == n->get_value()) {
        this->set_left(nullptr);
    }
    else {
        this->set_right(nullptr);
    }
}

template<class T>
AVLNode<T>* AVLNode<T>::get_max() {
    AVLNode<T>* right = this->get_right();
    if (right == nullptr) {
        return this;
    }
    else {
        return right->get_max();
    }
}

template<class T>
AVLNode<T>* AVLNode<T>::get_min() {
    AVLNode<T>* left = this->get_left();
    if (left == NULL) {
        return this;
    }
    else {
        return left->get_min();
    }
}

template<class T>
void AVLNode<T>::print_node() {

    std::cout << "I am at " << this->get_value() << " my height is " << this->get_height() <<
              " height diff is " << this->get_height_diff() << std::endl;
}

template<class T>
AVLTree<T>::AVLTree() {
    root = nullptr;
}

template<class T>
AVLTree<T>::~AVLTree() = default;

template<class T>
void AVLTree<T>::add_value(T v) {
    if (root == nullptr) {
        root = new AVLNode<T>(v);
    }
    else {
        AVLNode<T>* new_node = add_value(root, v);
        traverse_backwards(new_node->get_father());
    }

}

template<class T>
void AVLTree<T>::destroy_tree() {
    destroy_tree(root);
}

template<class T>
void AVLTree<T>::destroy_tree(AVLNode<T>* node) {
    if (node != nullptr) {
        destroy_tree(node->get_left());
        destroy_tree(node->get_right());
        delete node;
    }
}

template<class T>
void AVLTree<T>::remove_value(T v) {

    AVLNode<T>* found_node = find_value(root, v);
    if (found_node != nullptr) {
        AVLNode<T>* backtrack_node = remove_node(found_node);
        if (backtrack_node != nullptr) {
            traverse_backwards(backtrack_node);
        }
    }
}

template<class T>
void AVLTree<T>::rotate_left(AVLNode<T>* node_x) {

    AVLNode<T>* node_y;

    node_y = node_x->get_right();
    node_x->set_right(node_y->get_left());

    node_y->set_father(node_x->get_father());

    if (node_y->get_father() == nullptr) {
        root = node_y;
    }
    else {
        node_x->get_father()->set_son(node_y);
    }

    node_y->set_left(node_x);
    node_x->update_height();
    node_y->update_height();
}

template<class T>
void AVLTree<T>::rotate_right(AVLNode<T>* node_x) {

    AVLNode<T>* node_y;

    node_y = node_x->get_left();
    node_x->set_left(node_y->get_right());

    node_y->set_father(node_x->get_father());

    if (node_y->get_father() == nullptr) {
        root = node_y;
    }
    else {
        node_x->get_father()->set_son(node_y);
    }
    node_y->set_right(node_x);
    node_x->update_height();
    node_y->update_height();
}

template<class T>
AVLNode<T>* AVLTree<T>::add_value(AVLNode<T>* node, T v) { // Assumir valores diferentes a serem inseridos
    T value = node->get_value();
    if (v > value) {// Right
        AVLNode<T>* node_right = node->get_right();
        if (node_right == nullptr) {
            AVLNode<T>* new_node = new AVLNode<T>(v);
            node->set_right(new_node);
            return new_node;
        }
        else {
            return add_value(node_right, v);
        }
    }
    else { // Left
        AVLNode<T>* node_left = node->get_left();
        if (node_left == nullptr) {
            AVLNode<T>* new_node = new AVLNode<T>(v);
            node->set_left(new_node);
            return new_node;
        }
        else {
            return add_value(node_left, v);
        }
    }
}

template<class T>
AVLNode<T>* AVLTree<T>::lookup(T v) {
    return find_value(root, v);
}

template<class T>
double AVLTree<T>::get_ratio() {
    int n_nodes = get_n_nodes(root);
    int height = get_height(root);
    return height / (log(n_nodes) / (log(2)));

}

template<class T>
int AVLTree<T>::get_n_nodes(AVLNode<T>* node) {
    return (node == NULL) ? 0 : 1 + get_n_nodes(node->get_left()) + get_n_nodes(node->get_right());
}

template<class T>
int AVLTree<T>::get_height(AVLNode<T>* node) {
    return (node == NULL) ? 0 : 1 + std::max(get_height(node->get_left()), get_height(node->get_right()));
}

template<class T>
AVLNode<T>* AVLTree<T>::find_value(AVLNode<T>* node, T v) {
    T value = node->get_value();
    if (v == value) {
        return node;
    }
    else {
        AVLNode<T>* new_node = (v > value) ? node->get_right() : node->get_left();
        if (new_node == nullptr) {
            return nullptr;
        }
        else {
            return find_value(new_node, v);
        }
    }
}

template<class T>
AVLNode<T>* AVLTree<T>::remove_node(AVLNode<T>* node) {

    AVLNode<T>* father = node->get_father();
    AVLNode<T>* left_node = node->get_left();
    AVLNode<T>* right_node = node->get_right();
    if (node->get_height() == 0) { // leaf
        if (father == nullptr) { // root
            root = nullptr;
        }
        else { // have to remove link from father
            father->delete_son(node);
        }
    }
    else if (right_node == nullptr) { // only have left son
        if (father == nullptr) {
            root = left_node;
        }
        else {
            father->set_son(left_node);
        }
    }
    else if (left_node == nullptr) { // only have right son
        if (father == nullptr) {
            root = right_node;
        }
        else {
            father->set_son(right_node);
        }
    }
    else {
        AVLNode<T>* new_root = left_node->get_max();
        AVLNode<T>* backtrack_node = new_root->get_father(); // exemplo raul
        if (backtrack_node->get_value() == node->get_value()) {// exemplo nao raul
            backtrack_node = new_root;
        }
        new_root->get_father()->set_son(new_root->get_left());
        if (father != nullptr) {
            father->set_son(new_root);
        }
        else {
            new_root->set_father(nullptr);
            root = new_root;
        }
        if (left_node->get_value() != new_root->get_value()) {
            new_root->set_left(left_node);
        }
        else { // case where we new root is the left node (dont want cycles)
            new_root->set_left(left_node->get_left());
        }
        new_root->set_right(right_node);
        delete node;
        return backtrack_node;

    }
    //delete node;
    return father;
}


template<class T>
void AVLTree<T>::traverse_backwards(AVLNode<T>* node) {

    node->update_height();
    AVLNode<T>* new_root = node;
    int diff = node->get_height_diff();

    if (diff < -1) { // left deeper
        int left_diff = node->get_left()->get_height_diff();

        if (left_diff <= 0) {
            // left -> left case1 @ example if both heights are now equal we keep going in the same direction (left)
            new_root = node->get_left();
            this->rotate_right(node);

        }
        else {
            // left -> right case3 @ example
            new_root = node->get_left()->get_right();
            this->rotate_left(node->get_left());
            this->rotate_right(node);
        }

    }
    else if (diff > 1) { // right deeper

        int right_diff = node->get_right()->get_height_diff();

        if (right_diff < 0) { // right->left case4

            new_root = node->get_right()->get_left();
            this->rotate_right(node->get_right());
            this->rotate_left(node);

        }
        else { // right->right case2

            new_root = node->get_right();
            this->rotate_left(node);
        }
    }

    AVLNode<T>* father = new_root->get_father();

    if (father == nullptr) {
        root = new_root;
        return;
    }

    traverse_backwards(father);
}

template<class T>
void AVLTree<T>::iterate_tree(FILE* file) {

    int v, option = 1;
    if (file != nullptr) {

        int n_inserts, n_removes, n_lookups;
        fscanf(file, "%d%d%d%d", &option, &n_inserts, &n_removes, &n_lookups);
        /*double min_ratio = 100000;
        double max_ratio = 0;
        double avg_ratio = 0;*/
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        for (int i = 0; i < n_inserts; i++) {
            fscanf(file, "%d", &v);
            add_value(v);
            /*if (i > 3) {
                double ratio = get_ratio();
                min_ratio = std::min(ratio, min_ratio);
                max_ratio = std::max(ratio, max_ratio);
                avg_ratio += ratio;
                if (ratio < 1 || ratio >= 1.44)
                    printf("ratio = %lf at %d\n", ratio, i);
            }*/
        }
        /*avg_ratio = avg_ratio/(n_inserts - 4);
        printf("min ratio = %lf, max_ratio = %lf, avg_ratio = %lf\n", min_ratio, max_ratio, avg_ratio);*/
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
                  << " milliseconds for insertion" << std::endl;
        begin = std::chrono::steady_clock::now();
        for (int i = 0; i < n_removes; i++) {
            fscanf(file, "%d", &v);
            remove_value(v);
        }
        end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
                  << " milliseconds for removal" << std::endl;
        begin = std::chrono::steady_clock::now();
        for (int i = 0; i < n_lookups; i++) {
            fscanf(file, "%d", &v);
            lookup(v);
        }
        end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
                  << " milliseconds for lookups" << std::endl;
    }

    if (option == 0) {
        //destroy_tree();
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

    AVLNode<T>* n = root;
    while (true) {

        if (n != nullptr) {
            n->print_node();
        }
        scanf("\n%c", &cmd);
        switch (cmd) {
            case 'l' : {
                AVLNode<T>* left = n->get_left();
                if (left == nullptr) {
                    printf("Not going to NULL Node\n");
                }
                else {
                    n = left;
                }
                break;
            }

            case 'r' : {
                AVLNode<T>* right = n->get_right();
                if (right == nullptr) {
                    printf("Not going to NULL Node\n");
                }
                else {
                    n = right;
                }
                break;
            }


            case 't' : {
                if (n == root) {
                    printf("Already at root\n");
                }
                else {
                    n = n->get_father();
                }
            }
                break;

            case 'q' : {
                this->destroy_tree();
                return;
            }

            case 'a' : {
                scanf("%d", &v);
                this->add_value(v);
                n = root;


            }
                break;
            case 'd' : {
                scanf("%d", &v);
                this->remove_value(v);
                n = root;
            }
                break;
            default :
                printf("Unknown cmd\n");
        }
    }
}
