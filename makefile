generator: hash_functions.o
	g++ -c generator.cpp
	g++ -o g generator.o hash_functions.o
hash:
	g++ -c hash_functions.cpp
tester: hash_functions.o
	g++ -c tester.cpp
	g++ -o t tester.o hash_functions.o
clean:
	del *.o *.exe