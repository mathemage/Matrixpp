CC = g++
#CFLAGS = -g -O2
CFLAGS = -O2
OBJECTS = matrixpp.o io.o

#Matrix++ : $(OBJECTS)
#	$(CC) $(CFLAGS) $(OBJECTS) -o Matrix++ && rm $(OBJECTS)

io.exe : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o io.exe && rm $(OBJECTS)

%.o : %.cpp
	ctags *.cpp *.hpp -R && $(CC) $(CFLAGS) -c $<

clean:
	rm $(OBJECTS)
	rm *.exe
