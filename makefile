CXX=g++
CXXFLAGS=-Wall -pedantic

test_stack1.x: stack.hpp stack.h test_stack1.cpp
	$(CXX) $(CXXFLAGS) -o $@ test_stack1.cpp

in2post.x: stack.hpp stack.h in2post.cpp
	$(CXX) $(CXXFLAGS) -o $@ in2post.cpp

.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f *.o *.x core.*

%.x : %.c
	$(CC) -o $@ $<
%.x : %.cpp
	$(CXX) -o $@ $<
