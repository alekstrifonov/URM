run: main.o SparseArray.o tokenizer.o URM.o
	g++ main.o SparseArray.o tokenizer.o URM.o -o run

main.o: main.cpp
	g++ -c main.cpp -std=c++11 -o main.o

SparseArray.o: SparseArray.cpp
	g++ -c SparseArray.cpp -std=c++11 -o SparseArray.o

tokenizer.o: tokenizer.cpp
	g++ -c tokenizer.cpp -std=c++11 -o tokenizer.o

URM.o: URM.cpp
	g++ -c URM.cpp -std=c++11 -o URM.o

clean:
	rm *.o run