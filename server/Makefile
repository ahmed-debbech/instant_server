all: hello

hello:
	gcc server.c utils.c store.c -o server 
	./server
	echo "\n";

clean:
	echo "Cleaning up..."
	rm server