#include "AVL.cpp"

int main(int argc, char** argv) {

    FILE* file = nullptr;

    if (argc > 1) {
        file = fopen(argv[1], "r");
    }

    AVLTree<int>* t = new AVLTree<int>();
    t->iterate_tree(file);
    delete t;

    fclose(file);

    return 0;
}
