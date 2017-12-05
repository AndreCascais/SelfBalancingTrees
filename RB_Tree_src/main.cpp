#include "RB.cpp"
#include "Integer.hpp"

int main(int argc, char** argv) {

    std::string file_name;

    if (argc > 1) {
        file_name = argv[1];
    }

    auto t = new RBTree<intWrapper, intWrapper>();
    t->iterate_tree(file_name);
    delete t;

    return 0;
}
