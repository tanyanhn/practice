CC := g++
CPPFLAGS = -O0 -g -D_GLIBCXX_DEBUG

#TARGET=main

.PHONY: clean clear test run all doxygen
.SUFFIXES: .o .cpp .ex

#doxygen: doxygen.cfg
#	doxygen doxygen.cfg

FUNCTOR = TriangleIntersection.h SegmentIntersection.h Triangulation.h YinsetContainTriangle.h \
FindNearTriangle.h FaceContainFace.h

DATASTRUCT = Data.h Tol.h Point.h Segment.h Planar.h Face.h Yinset.h Direction.h Line.h Flat.h

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

Data.o: Data.cpp Point.h Segment.h Planar.h Face.h HassNode.h $(FUNCTOR)

Direction.o: Direction.cpp Tol.h Direction.h

Face.o: Face.cpp Data.h Face.h Planar.h Point.h

FaceContainFace.o: FaceContainFace.cpp Face.h Planar.h YinsetContainTriangle.h FaceContainFace.h

FindNearTriangle.o: FindNearTriangle.cpp Planar.h Data.h Tol.h FindNearTriangle.h

Flat.o: Flat.cpp Point.h Direction.h Tol.h Line.h Det.h Data.h Segment.h Flat.h

Line.o: Line.cpp Direction.h Point.h Tol.h Line.h Flat.h

Planar.o: Planar.cpp Point.h Segment.h Flat.h Direction.h Data.h Planar.h Line.h

Point.o: Point.cpp Direction.h Tol.h Data.h Point.h

Segment.o: Segment.cpp Segment.h Point.h Line.h Direction.h Tol.h Data.h Flat.h

SegmentIntersection.o: SegmentIntersection.cpp SegmentIntersection.h Planar.h \
TriangleIntersection.h Data.h Tol.h

Tol.o: Tol.cpp Tol.h Line.h Direction.h

Triangulation.o: Triangulation.cpp Triangulation.h Tol.h $(DATASTRUCT)

Yinset.o: Yinset.cpp Yinset.h HassNode.h Data.h $(FUNTOR)

YinsetContainTriangle.o: YinsetContainTriangle.cpp YinsetContainTriangle.h Data.h Tol.h  \
$(DATASTRUCT)

TriangleIntersection.o: TriangleIntersection.cpp TriangleIntersection.h Data.h Tol.h Segment.h \
Planar.h

test: test.ex
	rm -f core-test.ex*
	./test.ex

run: main.ex
	./main.ex

doxygen: doxygen.cfg
	doxygen doxygen.cfg

clear:
	-rm main.ex *.o test.ex core*

clean:
	-rm -f main.ex *.output *.o *.h.gch *.obj core* test.ex
	-rm -rf ./doxygen/
