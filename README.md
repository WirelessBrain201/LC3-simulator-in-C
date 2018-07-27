# LC3-simulator-in-C
An LC3 simulator made in C. It takes the filename of a .obj file as an input in the CLI, interprets the LC3 machine code and simulates running that code. The contents of each register are printed after each line of machine code is executed.

Some important notes:
This was made for an assignment, so it is not a full featured simulator. It can operate the following functions: TRAP, LD, LEA, LDI, AND, NOT, ADD, and BRZ.
For TRAP instructions, the program assumes it is a HALT.
