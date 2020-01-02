CC = g++

#TARGET=main

all: main.o main

#.cpp.o :
#	$(CC) -o $@ -c $<
#.o.ex :
#	$(CC) -o $@ $^

main : Point.cpp Line.cpp Jordanline.cpp Spajor.cpp Sweepline.cpp \
main.cpp Point.h Line.h Jordanline.h Spajor.h Sweepline.h BalanceTree.h \
HassNode.h
	$(CC) $^ -o $@

#main : main.o
#	$(CC) -o $@ $<

run: main
	./main ../panda.input ../mickey.input p-meet-m.output p-join-m.output p-complement.output m-complement.output

clean:
	-rm -f main *.output *o *.h.gch

