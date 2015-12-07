all:
	(cd src; make all)

clean:
	(cd src; make clean) && rm *.s

.PHONY: all clean
