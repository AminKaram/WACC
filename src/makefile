all: parser

OBJS = scanner.o parser.o main.o parsing-driver.o 

CPPFLAGS = -Wno-deprecated-register

%.o: %.cppi %.hh
	g++ -c $(CPPFLAGS) -o $@ $<

parser.cpp: parser.yy
	bison --report=solved,state -d -o $@ $<
	
parser.hpp: parser.cpp

scanner.cpp: scanner.l parser.hpp
	flex -o $@ $^

main : $(OBJS)
	g++ -o $@ $^
   
clean:
	$(RM) -rf parser.output parser.cpp parser.hpp parser scanner.cpp $(OBJS)

