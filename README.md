# SelfBalancingTrees
AVL and red-black tree implementation

# Making 
mkdir build
cd build
cmake ..
make

# Input generation
besides the available inputs, we added a inputs generator script,

cd Inputs
./input_generator ADDS REMOVES LOOKUPS

the script generates a file with the desired number of adds, removes and lookups (only removes, lookups existing values).
the input file structure should be:

0/1 	- don't go / go to interactive mode
ADDS 	- number of adds
REMOVES - number of removes
LOOKUPS - number of lookups
VALUES 	- the desired values

# Program usage
./execs/AVLTree INPUTFILE

if option 1 is used, the program will go to an interactive CLI where you can press h for help.


