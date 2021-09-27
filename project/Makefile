WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose
TESTFALGS = -DTEST_READARRAY -DTEST_SAVEARRAY -DTEST_SORTARRAY

SRCS = pa1.c shell_array.c shell_list.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	$(GCC) $(OBJS) -o main

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

testall: test1 test2 test3 test4 test5 test6 test7 test8 test9

test1: main
	./main output1.b out1.b
	diff examples/15.b out1.b
test2: main
	./main examples/15sa.b output2.b
test3: main
	./main examples/15sl.b output3.b
test4: main
	./main examples/1k.b output4.b
test5: main
	./main examples/1ksa.b output5.b
test6: main
	./main examples/1ksl.b output6.b
test7: main
	./main examples/10k.b output7.b
test8: main
	./main examples/100k.b output8.b
test9: main
	./main examples/1M.b output9.b

memory: main
	$(VAL) ./main examples/15.b output1.b

clean: # remove all machine generated files
	rm -f main *.o output? vallog testgen
