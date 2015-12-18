all: main 

OBJS = scanner.o parser.o preprocessor.o main.o parsing-driver.o astnode.o symbol-table.o front-end.o back-end.o semantic-id.o code-generation-visitor.o semantic-visitor.o

CPPFLAGS = -fmax-errors=20 -std=c++11 -Wno-deprecated-register -g

main.o: main.cc front-end.o back-end.o preprocessor.o
	g++ -c -g $(CPPFLAGS) -o $@ $<

preprocessor.o: preprocessor.cc preprocessor.hh
	g++ -c -g $(CPPFLAGS) -o $@ $<

code-generation-visitor.o: code-generation-visitor.cc ast-node-visitor.hh	
	g++ -c -g $(CPPFLAGS) -o $@ $<

semantic-id.o: semantic-id.cc semantic-id.hh
	g++ -c -g $(CPPFLAGS) -o $@ $<

back-end.o: back-end.cc back-end.hh code-generation-visitor.o
	g++ -c -g $(CPPFLAGS) -o $@ $<

front-end.o: front-end.cc front-end.hh parser.o semantic-visitor.o
	g++ -c -g $(CPPFLAGS) -o $@ $<

astnode.o: astnode.cc astnode.hh
	g++ -c -g $(CPPFLAGS) -o $@ $<

parsing-driver.o: parsing-driver.cc parsing-driver.hh parser.o 
	g++ -c -g $(CPPFLAGS) -o $@ $<

semantic-visitor.o: semantic-visitor.cc ast-node-visitor.hh astnode.o semantic-id.o symbol-table.o parser.hh
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
