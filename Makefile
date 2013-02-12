CC = g++
#CFLAGS = -g -O2
CFLAGS = -O2
OBJECTS = main.o Matrix++.o lnum.o

Matrix++ : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o Matrix++ && rm $(OBJECTS)

%.o : %.cpp
	ctags *.cpp *.hpp -R && $(CC) $(CFLAGS) -c $<

clean:
	rm $(OBJECTS)
	rm Matrix++
