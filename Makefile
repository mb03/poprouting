CFLAGS+=-lm -ldl -ljson-c -pthread -g
poprouting:out libs logger #cpp
	cp prince/src/common_c.h prince/src/common.h
	$(CC) $(LDFLAGS) -Dunique prince/src/prince.c prince/src/lib/ini.c performance_measure/performance.c prince/src/parser.c prince/src/socket.c graph-parser_c/src/brandes.c graph-parser_c/src/biconnected.c  graph-parser_c/src/graph_parser.c graph-parser_c/src/graph/graph.c graph-parser_c/src/graph/list.c graph-parser_c/src/network_change.c -o output/prince_c   $(CFLAGS)
libs:
	cp prince/src/common_c.h prince/src/common.h
	$(CC) -shared -fPIC -o  output/libprince_olsr_c.so  prince/src/olsr.c prince/src/socket.c prince/src/parser.c graph-parser_c/src/brandes.c graph-parser_c/src/biconnected.c  graph-parser_c/src/graph_parser.c graph-parser_c/src/graph/graph.c graph-parser_c/src/graph/list.c graph-parser_c/src/network_change.c
	$(CC) -shared -fPIC -o  output/libprince_oonf_c.so prince/src/oonf.c prince/src/socket.c prince/src/parser.c graph-parser_c/src/brandes.c graph-parser_c/src/biconnected.c  graph-parser_c/src/graph_parser.c graph-parser_c/src/graph/graph.c graph-parser_c/src/graph/list.c graph-parser_c/src/network_change.c
	rm prince/src/common.h
cpp:
	$(MAKE) -C graph-parser/src
	cp prince/src/common_c++.h prince/src/common.h
	$(CXX) prince/src/prince.c prince/src/parser.c prince/src/lib/ini.c performance_measure/performance.c -g  --std=c++11 -Lgraph-parser/build -lgraphparser -Wwrite-strings -ldl -ljson-c -o output/prince  
	$(MAKE) -C prince/src libprince_olsr.so
	$(MAKE) -C prince/src libprince_oonf.so
	cp prince/build/* output/
	rm prince/src/common.h

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf output

out:
	mkdir -p output
	mkdir -p prince/build/
	mkdir -p graph-parser/build/
install:
	cp graph-parser/build/libgraphparser.so /usr/lib/
	cp output/libprince_oonf.so /usr/lib/
	cp output/libprince_olsr.so /usr/lib/
	cp output/libprince_oonf_c.so /usr/lib/
	cp output/libprince_olsr_c.so /usr/lib/
	cp output/prince_c /usr/bin/
	cp output/prince /usr/bin
logger:
	$(CC) performance_measure/performance_runner.c performance_measure/performance.c -o output/prince_logger
uninstall:
	rm -f /usr/lib/libgraphparser.so
	rm -f /usr/lib/libprince_oonf.so
	rm -f /usr/lib/libprince_olsr.so
	rm -f /usr/lib/libprince_oonf_c.so
	rm -f /usr/lib/libprince_olsr_c.so
	rm -f /usr/bin/prince
	rm -f /usr/bin/prince_c
	rm -fr prince/build/
	rm -fr graph-parser/build/
	
	

