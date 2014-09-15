all: tests

run: tests
	./tests

tests: tests.o
	g++ -g $^ -o $@

tests.o: tests.cpp arturo.h
	g++ -c -g $< -o $@

clean:
	rm -f tests
	rm -f *.o
