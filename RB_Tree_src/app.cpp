#include "main.cpp"

int main(int argc, char** argv) {

    FILE* file = nullptr;

    if (argc > 1) {
        file = fopen(argv[1], "r");
    }

    auto t = new RBTree<int*, int*>();
//    auto t = new RBTree<std::string, std::string>();
    t->iterate_tree(file);
    delete t;

    return 0;
}
