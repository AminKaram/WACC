all: main 

OBJS = scanner.o parser.o main.o parsing-driver.o 

CPPFLAGS = -fmax-errors=20 

%.o: %.cc %.hh
	g++ -c $(CPPFLAGS) -o $@ $<

parser.cc: parser.yy
	bison --report=solved,state -d -o $@ $<
	
parser.hh: parser.cc

scanner.cc: scanner.l parser.hh
	flex -o $@ $^

main : $(OBJS)
	g++ $^ -o $@
   
clean:
	$(RM) -rf location.hh position.hh stack.hh parser.output parser.cc parser.hh parser scanner.cc $(OBJS)

.PHONY: all clean
