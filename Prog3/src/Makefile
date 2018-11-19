useGraph.exe: useGraph.o heap.o hash.o graph.o
	g++ -o useGraph.exe useGraph.o heap.o hash.o graph.o

useGraph.o: useGraph.cpp
	g++ -c useGraph.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

debug:
	g++ -g -o useGraphDebug.exe useGraph.cpp heap.cpp hash.cpp graph.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups