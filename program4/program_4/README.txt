Compiler design program #4
Zongze Li
11018849
zongzeli2@my.unt.edu

Features:
1) Including all the features of program #3.
2) Supported function call.
3) Supported bitwise.
4) Supported global variable declare and local variable declare. There will be no confilct between global variable to local variable of between different function's local variables.

How to run:
Type in command "make", there will generate a complier file "compiler". Then you can use it to compile *.ct files.

Easy to test:
The folder included the latest version of CMachine file and all the *.ct test files. And there is a test script "test.sh". If you hope to test all the test files, you can just type in command "sh test.sh". Then the script will re-generate the compiler and compile all the *.ct files, then it will test the compiled *.C file with CMachine. 

Problems:
All the *.ct files can be compiled and pass CMachine test except bitwise. Because the operator "~" can't be recognized by CMachine.
