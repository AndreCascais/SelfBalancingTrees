#GENERAL CONFIG ZONE
cmake_minimum_required(VERSION 3.0)
project(SelfBalancingTrees)

#set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 14)


#LOCATE SOURCE FILES ZONE
file(GLOB AVLTREE_HDR "${PROJECT_SOURCE_DIR}/AVL_Tree_src/*.hpp")
file(GLOB AVLTREE_SRC "${PROJECT_SOURCE_DIR}/AVL_Tree_src/*.cpp")

file(GLOB RBTREE_HDR "${PROJECT_SOURCE_DIR}/RB_Tree_src/*.hpp")
file(GLOB RBTREE_SRC "${PROJECT_SOURCE_DIR}/RB_Tree_src/*.cpp")

file(GLOB SplayTREE_HDR "${PROJECT_SOURCE_DIR}/Splay_Tree_src/*.hpp")
file(GLOB SplayTREE_SRC "${PROJECT_SOURCE_DIR}/Splay_Tree_src/*.cpp")

set(List_SRC "${PROJECT_SOURCE_DIR}/List_src/List.cpp")


#EXECUTABLES ZONE
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/execs)

add_executable(RBTree ${RBTREE_SRC} ${RBTREE_HDR})
add_executable(AVLTree ${AVLTREE_SRC} ${AVLTREE_HDR})
add_executable(SplayTree ${SplayTREE_SRC} ${SplayTREE_HDR})
add_executable(List ${List_SRC})


#TESTS ZONE
enable_testing()
add_test(RB - 1000I999R0L ../execs/RBTree ../Inputs/1000I999R0L.txt)
add_test(RB - 10000I9999R0L ../execs/RBTree ../Inputs/10000I9999R0L.txt)
add_test(RB - 100000I99999R0L ../execs/RBTree ../Inputs/100000I99999R0L.txt)
add_test(RB - 1000000I999999R0L ../execs/RBTree ../Inputs/1000000I999999R0L.txt)
add_test(RB - 10000000I9999999R0L ../execs/RBTree ../Inputs/10000000I9999999R0L.txt)

add_test(RB - 1000I0R1000L ../execs/RBTree ../Inputs/1000I0R1000L.txt)
add_test(RB - 10000I0R10000L ../execs/RBTree ../Inputs/10000I0R10000L.txt)
add_test(RB - 100000I0R100000L ../execs/RBTree ../Inputs/100000I0R100000L.txt)
add_test(RB - 1000000I0R1000000L ../execs/RBTree ../Inputs/1000000I0R1000000L.txt)
add_test(RB - 10000000I0R10000000L ../execs/RBTree ../Inputs/10000000I0R10000000L.txt)


add_test(AVL - 1000I999R0L ../execs/AVLTree ../Inputs/1000I999R0L.txt)
add_test(AVL - 10000I9999R0L ../execs/AVLTree ../Inputs/10000I9999R0L.txt)
add_test(AVL - 100000I99999R0L ../execs/AVLTree ../Inputs/100000I99999R0L.txt)
add_test(AVL - 1000000I999999R0L ../execs/AVLTree ../Inputs/1000000I999999R0L.txt)
add_test(AVL - 10000000I9999999R0L ../execs/AVLTree ../Inputs/10000000I9999999R0L.txt)

add_test(AVL - 1000I0R1000L ../execs/AVLTree ../Inputs/1000I0R1000L.txt)
add_test(AVL - 10000I0R10000L ../execs/AVLTree ../Inputs/10000I0R10000L.txt)
add_test(AVL - 100000I0R100000L ../execs/AVLTree ../Inputs/100000I0R100000L.txt)
add_test(AVL - 1000000I0R1000000L ../execs/AVLTree ../Inputs/1000000I0R1000000L.txt)
add_test(AVL - 10000000I0R10000000L ../execs/AVLTree ../Inputs/10000000I0R10000000L.txt)


add_test(Splay - 1000I999R0L ../execs/AVLTree ../Inputs/1000I999R0L.txt)
add_test(Splay - 10000I9999R0L ../execs/AVLTree ../Inputs/10000I9999R0L.txt)
add_test(Splay - 100000I99999R0L ../execs/AVLTree ../Inputs/100000I99999R0L.txt)
add_test(Splay - 1000000I999999R0L ../execs/AVLTree ../Inputs/1000000I999999R0L.txt)
add_test(Splay - 10000000I9999999R0L ../execs/AVLTree ../Inputs/10000000I9999999R0L.txt)

add_test(Splay - 1000I0R1000L ../execs/AVLTree ../Inputs/1000I0R1000L.txt)
add_test(Splay - 10000I0R10000L ../execs/AVLTree ../Inputs/10000I0R10000L.txt)
add_test(Splay - 100000I0R100000L ../execs/AVLTree ../Inputs/100000I0R100000L.txt)
add_test(Splay - 1000000I0R1000000L ../execs/AVLTree ../Inputs/1000000I0R1000000L.txt)
add_test(Splay - 10000000I0R10000000L ../execs/AVLTree ../Inputs/10000000I0R10000000L.txt)