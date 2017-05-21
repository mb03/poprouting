all: 
	mkdir -p output
	$(CC) graph-parser_c/src/graph/graph.c graph-parser_c/src/graph/list.c graph-parser_c/src/network_change.c graph-parser_c/src/local_exe.c graph-parser_c/src/brandes.c graph-parser_c/src/biconnected.c graph-parser_c/src/runner.c -o output/prince_c
clean:
	rm -fr output
	rm -f *~


