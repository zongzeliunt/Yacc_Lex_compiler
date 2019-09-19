echo "make clean"
make clean
echo "make new compiler"
make
echo "1"
./compiler < CTranPgms/one.ct
./assembler < cmachine_exe.c
echo "2"
./compiler < CTranPgms/two.ct
./assembler < cmachine_exe.c
echo "3"
./compiler < CTranPgms/three.ct
./assembler < cmachine_exe.c
echo "4"
./compiler < CTranPgms/four.ct
./assembler < cmachine_exe.c
echo "5"
./compiler < CTranPgms/five.ct
./assembler < cmachine_exe.c
echo "6"
./compiler < CTranPgms/six.ct
./assembler < cmachine_exe.c
echo "7"
./compiler < CTranPgms/seven.ct
./assembler < cmachine_exe.c
echo "8"
./compiler < CTranPgms/eight.ct
./assembler < cmachine_exe.c
echo "9"
./compiler < CTranPgms/nine.ct
./assembler < cmachine_exe.c
echo "10"
./compiler < CTranPgms/ten.ct
./assembler < cmachine_exe.c
echo "hanoi"
./compiler < CTranPgms/hanoi.ct
./assembler < cmachine_exe.c
echo "mod"
./compiler < CTranPgms/mod.ct
./assembler < cmachine_exe.c
echo "scope"
./compiler < CTranPgms/scope.ct
./assembler < cmachine_exe.c
echo "multiDimension"
./compiler < CTranPgms/multiDimension.ct
./assembler < cmachine_exe.c
echo "types"
./compiler < CTranPgms/types.ct
./assembler < cmachine_exe.c
echo "bubble"
./compiler < CTranPgms/bubble.ct
./assembler < cmachine_exe.c
echo "factorial"
./compiler < CTranPgms/factorial.ct
./assembler < cmachine_exe.c

#echo "bitwise"
#./compiler < CTranPgms/bitwise.ct
#./assembler < cmachine_exe.c
#"~" can't be supported
