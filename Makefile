build/task: build/main.o build/quadratic.o build/test.o build/common.o
	g++ -fsanitize=address build/main.o build/quadratic.o build/test.o build/common.o -o build/task

build/main.o: main.cpp quadratic.h test.h
	g++ -std=c++20 -Wall -Ofast -unroll-loops -fno-stack-protector -fsanitize=address -c main.cpp -o build/main.o

build/quadratic.o: quadratic.cpp quadratic.h common.h
	g++ -std=c++20 -Wall -Ofast -unroll-loops -fno-stack-protector -fsanitize=address -c quadratic.cpp -o build/quadratic.o

build/test.o: test.cpp quadratic.h common.h
	g++ -std=c++20 -Wall -Ofast -unroll-loops -fno-stack-protector -fsanitize=address -c test.cpp -o build/test.o

build/common.o: common.cpp common.h
	g++ -std=c++20 -Wall -Ofast -unroll-loops -fno-stack-protector -fsanitize=address -c common.cpp -o build/common.o
