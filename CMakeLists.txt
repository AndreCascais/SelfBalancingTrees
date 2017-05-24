cmake_minimum_required(VERSION 3.0)
project(SelfBalancingTrees)

#SET(CMAKE_VERBOSE_MAKEFILE true)

SET(CMAKE_CXX_STANDARD 14)


file(GLOB AVLTREE_HDR "${PROJECT_SOURCE_DIR}/AVL_Tree_src/*.h")
file(GLOB AVLTREE_SRC "${PROJECT_SOURCE_DIR}/AVL_Tree_src/*.cpp")

file(GLOB RBTREE_HDR "${PROJECT_SOURCE_DIR}/RB_Tree_src/*.h")
file(GLOB RBTREE_SRC "${PROJECT_SOURCE_DIR}/RB_Tree_src/*.cpp")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/execs)

add_executable(RBTree ${RBTREE_SRC} ${RBTREE_HDR})

add_executable(AVLTree ${AVLTREE_SRC} ${AVLTREE_HDR})

