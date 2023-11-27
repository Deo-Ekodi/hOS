# guide to add symbols to gdb
cd bin && echo "add-symbol-file ../build/kernelfull.o 0x100000" && gdb
