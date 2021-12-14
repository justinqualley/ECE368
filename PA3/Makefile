WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose --track-origins=yes
TESTFALGS = 

SRCS = main.c path.c file.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS)
	$(GCC) $(OBJS) -o pa3

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

t1: pa3
	./pa3 examples/4_5.b outputs/4_5.t outputs/4_5.f outputs/4_5.p
	diff examples/4_5.t outputs/4_5.t
	diff examples/4_5.f outputs/4_5.f
	diff examples/4_5.p outputs/4_5.p
t2: pa3
	./pa3 examples/5_4.b outputs/5_4.t outputs/5_4.f outputs/5_4.p
	diff examples/5_4.t outputs/5_4.t
	diff examples/5_4.f outputs/5_4.f
	diff examples/5_4.p outputs/5_4.p
t3: pa3
	./pa3 examples/5_5.b outputs/5_5.t outputs/5_5.f outputs/5_5.p
	diff examples/5_5.t outputs/5_5.t
	diff examples/5_5.p outputs/5_5.p
t4: pa3
	./pa3 examples/7_7.b outputs/7_7.t outputs/7_7.f outputs/7_7.p
	diff examples/7_7.t outputs/7_7.t
	diff examples/7_7.f outputs/7_7.f
	diff examples/7_7.p outputs/7_7.p
ta: t1 t2 t3 t4
m: pa3
	$(VAL) ./pa3 examples/4_5.b outputs/4_5.t outputs/4_5.f outputs/4_5.p
	tail vallog

clean: # remove all machine generated files
	rm -f main *.o output? vallog testgen
