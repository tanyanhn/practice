TARGET=main

main: window.cpp
	@$(CXX) window.cpp $(shell wx-config --libs std,gl,propgrid --cxxflags) -lGLEW -lGL -o ${OUTPUT}

