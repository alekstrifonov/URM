URM: main.o SparseArray.o tokenizer.o
	g++ main.o SparseArray.o tokenizer.o -o URM

main.o: main.cpp
	g++ -c main.cpp -std=c++11 -o main.o

SparseArray.o: SparseArray.cpp
	g++ -c SparseArray.cpp -std=c++11 -o SparseArray.o

tokenizer.o: tokenizer.cpp
	g++ -c tokenizer.cpp -std=c++11 -o tokenizer.o

clean:
	rm *.o URM
