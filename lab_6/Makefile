CXXFLAGS = -std=c++14 -Wall

all : test-regex

test-regex : regex.o test-regex.o testbase.o engine.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean :
	rm -f test-regex *.o *~

.PHONY : all clean

