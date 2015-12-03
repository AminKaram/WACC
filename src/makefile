all: main 

OBJS = scanner.o parser.o main.o parsing-driver.o astnode.o symbol-table.o semantic-id.o ast-node-visitor.o front-end.o 

CPPFLAGS = -fmax-errors=20 -std=c++11 -Wno-deprecated-register -g

main.o: main.cc front-end.o
	g++ -c -g $(CPPFLAGS) -o $@ $<

semantic-id.o: semantic-id.cc semantic-id.hh
	g++ -c -g $(CPPFLAGS) -o $@ $<

front-end.o: front-end.cc front-end.hh parser.o ast-node-visitor.o
	g++ -c -g $(CPPFLAGS) -o $@ $<

astnode.o: astnode.cc astnode.hh
	g++ -c -g $(CPPFLAGS) -o $@ $<

parsing-driver.o: parsing-driver.cc parsing-driver.hh parser.o
	g++ -c -g $(CPPFLAGS) -o $@ $<

ast-node-visitor.o: ast-node-visitor.cc ast-node-visitor.hh astnode.o semantic-id.o symbol-table.o parser.hh
	g++ -c -g $(CPPFLAGS) -o $@ $<

symbol-table.o: symbol-table.cc symbol-table.hh
	g++ -c -g $(CPPFLAGS) -o $@ $<

parser.cc: parser.yy
	bison --report=solved,state -d -o $@ $<
          
parser.hh: parser.cc
	
scanner.cc: scanner.l parser.hh
	flex -o $@ $^

main: $(OBJS)
	g++ -g $^ -o $@

clean:
	$(RM) -rf main location.hh position.hh stack.hh parser.output parser.cc parser.hh parser scanner.cc $(OBJS)
               
.PHONY: all clean
