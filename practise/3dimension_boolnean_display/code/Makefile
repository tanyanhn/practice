CC = g++

#TARGET=main



.cpp.o:
	$(CC) -o $@ -c $<
.o.ex:
	$(CC) -o $@ $^

main.ex: main.o Data.o Direction.o Face.o FaceContainFace.o FindNearTriangle.o Flat.o Line.o \
Planar.o TriangleIntersection.o \
Point.o Segment.o SegmentIntersection.o Tol.o Triangulation.o Yinset.o YinsetContainTriangle.o
	$(CC) $^ -o $@

#main : main.o
#	$(CC) -o $@ $<
main.o: main.cpp

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

run: main.ex
	./main.ex ./Data/cube.obj

clean:
	-rm -f main *.output *o *.h.gch
