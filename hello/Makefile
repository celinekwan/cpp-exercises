all: hello exercise

hello: hello.cpp 
	g++ -Wall -g $^ -o $@

exercise: exercise.cpp 
	g++ -Wall -g $^ -o $@
	
clean:
	rm -f *.o hello
	rm -f *.o exercise
