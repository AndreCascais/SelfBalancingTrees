# SelfBalancingTrees
This code was initially developed for a college course on Algorithms.

In it we've implemented AVL, Splay, and RedBlack Tree.

## Compiling the code
```bash
mkdir build
cd build
cmake ..
make
```

## Input generation
Besides the available inputs, we added a inputs generator script,

```bash
cd Inputs
./input_generator <ADDS> <REMOVES> <LOOKUPS>
```

The script generates a file with the desired number of adds, removes and lookups (it will only tey to remove or lookup existing values).

The input file structure should be:
```
1/0     - go / don't go into interactive mode
ADDS    - number of adds
REMOVES - number of removes
LOOKUPS - number of lookups
VALUES  - the desired values
```

## Program usage
```bash
./execs/AVLTree INPUTFILE
```

If option 1 is used, the program will go to an interactive CLI where you can press h for help.
