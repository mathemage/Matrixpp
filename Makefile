CC = g++
#CFLAGS = -g -O2
CFLAGS = -O2
OBJECTS = matrixpp.o

#Matrix++ : $(OBJECTS)
#	$(CC) $(CFLAGS) $(OBJECTS) -o Matrix++ && rm $(OBJECTS)

io.exe : $(OBJECTS) io.o
	$(CC) $(CFLAGS) $(OBJECTS) io.o -o io.exe ; rm $(OBJECTS)

arithmetics.exe : $(OBJECTS) arithmetics.o
	$(CC) $(CFLAGS) $(OBJECTS) arithmetics.o -o arithmetics.exe ; rm $(OBJECTS)

%.o : %.cpp
	ctags *.cpp *.hpp -R ; $(CC) $(CFLAGS) -c $<; echo $<

clean:
	rm $(OBJECTS)
	rm *.exe
