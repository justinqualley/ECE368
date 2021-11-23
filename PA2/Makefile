WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose --track-origins=yes
TESTFALGS = 

SRCS = tree.c main.c file.c eval.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS)
	$(GCC) $(OBJS) -o pa4

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

b0: pa4
	./pa4 -b examples/ops0.b output0.b
	diff examples/tree0.b output0.b
b1: pa4
	./pa4 -b examples/ops1.b output1.b
	diff examples/tree1.b output1.b
b2: pa4
	./pa4 -b examples/ops2.b output2.b
	diff examples/tree2.b output2.b
b3: pa4
	./pa4 -b examples/ops3.b output3.b
	diff examples/tree3.b output3.b
	
b: b0 b1 b2 b3

e0: pa4
	./pa4 -e examples/tree0.b
e1: pa4
	./pa4 -e examples/tree1.b
e2: pa4
	./pa4 -e examples/tree2.b
e3: pa4
	./pa4 -e examples/tree3.b
e0i: pa4
	./pa4 -e examples/invalidtree0.b
e1i: pa4
	./pa4 -e examples/invalidtree1.b
e2i: pa4
	./pa4 -e examples/invalidtree2.b
ei: e0i e1i e2i
e: e0 e1 e2 e3 ei
final: b e em bm
em: pa4
	$(VAL) ./pa4 -e examples/tree1.b
	tail vallog
bm: pa4
	$(VAL) ./pa4 -b examples/ops1.b outputs/output1.b 
	tail vallog

clean: # remove all machine generated files
	rm -f main *.o output? vallog testgen
