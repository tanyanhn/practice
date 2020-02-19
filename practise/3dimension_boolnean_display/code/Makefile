CC = g++
CPPFLAGS = -g -D_GLIBCXX_DEBUG

#TARGET=main

.PHONY: clean clear test run all doxygen
.SUFFIXES: .o .cpp .ex

#doxygen: doxygen.cfg
#	doxygen doxygen.cfg

.cpp.o:
	$(CC) -o $@ -c $< $(CPPFLAGS)
.o.ex:
	$(CC) -o $@ $^ $(CPPFLAGS)

all: main.ex test.ex

main.ex: main.o Data.o Direction.o Face.o FaceContainFace.o FindNearTriangle.o Flat.o Line.o \
Planar.o TriangleIntersection.o \
Point.o Segment.o SegmentIntersection.o Tol.o Triangulation.o Yinset.o YinsetContainTriangle.o
#	$(CC) $^ -o $@ -g

test.ex: test.o Data.o Direction.o Face.o FaceContainFace.o FindNearTriangle.o Flat.o Line.o \
Planar.o TriangleIntersection.o \
Point.o Segment.o SegmentIntersection.o Tol.o Triangulation.o Yinset.o YinsetContainTriangle.o
#	$(CC) $^ -o $@ -g

#main : main.o
#	$(CC) -o $@ $<
main.o: main.cpp

test.o: test.cpp

Data.o: Data.cpp

Direction.o: Direction.cpp

Face.o: Face.cpp

FaceContainFace.o: FaceContainFace.cpp

FindNearTriangle.o: FindNearTriangle.cpp

Flat.o: Flat.cpp

Line.o: Line.cpp

Planar.o: Planar.cpp

Point.o: Point.cpp

Segment.o: Segment.cpp

SegmentIntersection.o: SegmentIntersection.cpp

Tol.o: Tol.cpp

Triangulation.o: Triangulation.cpp

Yinset.o: Yinset.cpp

YinsetContainTriangle.o: YinsetContainTriangle.cpp

TriangleIntersection.o: TriangleIntersection.cpp

test: test.ex
	./test.ex

run: main.ex
	./main.ex

doxygen: doxygen.cfg
	doxygen doxygen.cfg

clear:
	-rm main.ex *.o

clean:
	-rm -f main.ex *.output *.o *.h.gch *.obj
	-rm -rf ./doxygen/
