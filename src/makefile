all: parser

OBJS = scanner.o parser.o main.o  

CPPFLAGS = -Wno-deprecated-register

%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $<

parser.cpp: parser.y
	bison --report=solved,state -d -o $@ $^
	
parser.hpp: parser.cpp

scanner.cpp: scanner.l parser.hpp
	flex -o $@ $^
  
scanner: $(OBJS)
	g++ -o $@ $(OBJS)

parser: $(OBJS)
	g++ -o $@ $(OBJS)  

clean:
	$(RM) -rf parser.output parser.cpp parser.hpp parser scanner.cpp $(OBJS)

