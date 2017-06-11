#include "main.cpp"

int main(int argc, char** argv) {

    FILE* file = nullptr;

    if (argc > 1) {
        file = fopen(argv[1], "r");
    }

    RBTree<int, int>* t = new RBTree<int, int>();
    t->iterate_tree(file);
    delete t;

    return 0;
}