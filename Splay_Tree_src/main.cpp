#include "Splay.cpp"

int main(int argc, char** argv) {

    FILE* file = nullptr;

    if (argc > 1) {
        file = fopen(argv[1], "r");
    }

    SplayTree<int>* t = new SplayTree<int>();
    t->iterate_tree(file);
    delete t;

    return 0;
}
