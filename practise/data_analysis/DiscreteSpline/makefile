CC := g++

CPPFLAGS = -O0 -g -D_GLIBCXX_DEBUG --std=c++11
MATLAB := matlab -nodesktop -nosplash -logfile `date +%Y_%m_%d-%H_%M_%S`.log -r

GSLLIB = -lgsl -lgslcblas -lm

LAPACKELIB = -llapacke -llapack -lblas

.PHONY: clean all
.SUFFIXES: .o .cpp .ex

.cpp.o:
	$(CC) -o $@ -c $< $(CPPFLAGS) $(LAPACKELIB) $(GSLLIB)
.o.ex:
	$(CC) -o $@ $^ $(CPPFLAGS) $(LAPACKELIB) $(GSLLIB)
.cpp.ex:
	$(CC) -o $@ $< $(CPPFLAGS) $(LAPACKELIB) $(GSLLIB)

all: PlotHeart.ex

#main.ex: main.cpp gsl_function.h Bspline.h
#	$(CC) -o $@ $< $(CPPFLAGS) $(LAPACKELIB) $(GSLLIB)
# main.ex: main.o

PlotHeart.ex: PlotHeart.cpp DiscreteSpline.h gsl_function.h

#run: main.ex PlotHeart.ex
#	./main.ex output1 output2
#	./PlotHeart.ex

#print: main.ex plotTruncatedPowerFunc2Bsplines.m p.m
#	./main.ex output1 output2
#	$(MATLAB) p

heart: PlotHeart.ex
	./PlotHeart.ex
	$(MATLAB) Heartplot

clear:
	-rm main.ex *.o core* *.log

clean:
	-rm -f main.ex *.output *.o *.h.gch *.obj core* test.ex *.log
	-rm -rf ./doxygen/
