all: compile 

compile:
	gcc-13 -Wall -Wextra -o build/GoL src/main.c

run:
	./build/GoL

clean:
	rm -rf ./build/*

.PHONY: clean
