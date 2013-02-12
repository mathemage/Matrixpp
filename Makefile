CC = g++
#CFLAGS = -g -O2
CFLAGS = -O2
OBJECTS = main.o matrixpp.o

Matrix++ : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o Matrix++ && rm $(OBJECTS)

%.o : %.cpp
	ctags *.cpp *.hpp -R && $(CC) $(CFLAGS) -c $<

clean:
	rm $(OBJECTS)
	rm Matrix++
