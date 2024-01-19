compile:
	g++ -Wall -pedantic-errors -g -o lab02.out lab02.cpp

run:
	./lab02.out -c ATTCGG
	./lab02.out -d 6 22 240

clean:
	rm lab02.out
