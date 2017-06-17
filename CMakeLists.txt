cmake_minimum_required(VERSION 3.0)
project(SelfBalancingTrees)

#SET(CMAKE_VERBOSE_MAKEFILE true)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


file(GLOB AVLTREE_HDR "${PROJECT_SOURCE_DIR}/AVL_Tree_src/*.hpp")
file(GLOB AVLTREE_SRC "${PROJECT_SOURCE_DIR}/AVL_Tree_src/*.cpp")

file(GLOB RBTREE_HDR "${PROJECT_SOURCE_DIR}/RB_Tree_src/*.hpp")
file(GLOB RBTREE_SRC "${PROJECT_SOURCE_DIR}/RB_Tree_src/*.cpp")

file(GLOB SplayTREE_HDR "${PROJECT_SOURCE_DIR}/Splay_Tree_src/*.hpp")
file(GLOB SplayTREE_SRC "${PROJECT_SOURCE_DIR}/Splay_Tree_src/*.cpp")


SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/execs)


add_executable(RBTree ${RBTREE_SRC} ${RBTREE_HDR})

add_executable(AVLTree ${AVLTREE_SRC} ${AVLTREE_HDR})

add_executable(SplayTree ${SplayTREE_SRC} ${SplayTREE_HDR})

set(listfiles "${PROJECT_SOURCE_DIR}/List_src/List.cpp")

add_executable(List ${listfiles})

enable_testing()
add_test(1000I999R0L ../execs/RBTree ../Inputs/1000I999R0L.txt)
add_test(10000I9999R0L ../execs/RBTree ../Inputs/10000I9999R0L.txt)
add_test(100000I99999R0L ../execs/RBTree ../Inputs/100000I99999R0L.txt)
add_test(1000000I999999R0L ../execs/RBTree ../Inputs/1000000I999999R0L.txt)
add_test(10000000I9999999R0L ../execs/RBTree ../Inputs/10000000I9999999R0L.txt)

add_test(1000I0R1000L ../execs/RBTree ../Inputs/1000I0R1000L.txt)
add_test(10000I0R10000L ../execs/RBTree ../Inputs/10000I0R10000L.txt)
add_test(100000I0R100000L ../execs/RBTree ../Inputs/100000I0R100000L.txt)
add_test(1000000I0R1000000L ../execs/RBTree ../Inputs/1000000I0R1000000L.txt)
add_test(10000000I0R10000000L ../execs/RBTree ../Inputs/10000000I0R10000000L.txt)
