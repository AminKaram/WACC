all: main 

OBJS = scanner.o parser.o main.o parsing-driver.o astnode.o symbol-table.o ast-node-visitor.o front-end.o

CPPFLAGS = -fmax-errors=20 -std=c++11 -Wno-deprecated-register

main.o: main.cc front-end.o
	g++ -c $(CPPFLAGS) -o $@ $<

front-end.o: front-end.cc front-end.hh parser.o ast-node-visitor.o
	g++ -c $(CPPFLAGS) -o $@ $<

astnode.o: astnode.cc astnode.hh
	g++ -c $(CPPFLAGS) -o $@ $<

parsing-driver.o: parsing-driver.cc parsing-driver.hh parser.o
	g++ -c $(CPPFLAGS) -o $@ $<

ast-node-visitor.o: ast-node-visitor.cc ast-node-visitor.hh astnode.o semantic-id.hh symbol-table.o
	g++ -c $(CPPFLAGS) -o $@ $<

symbol-table.o: symbol-table.cc symbol-table.hh
	g++ -c $(CPPFLAGS) -o $@ $<

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
