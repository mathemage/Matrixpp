CC = g++
CFLAGS = -O2
#OBJECTS = io.o arithmetics.o

#io.exe : $(OBJECTS) io.o
	#$(CC) $(CFLAGS) $(OBJECTS) io.o -o io.exe ; rm $(OBJECTS)

%.exe : %.o
	$(CC) $(CFLAGS) $? -o $@ ; rm $?

%.o : %.cpp
	ctags *.cpp *.hpp -R ; $(CC) $(CFLAGS) -c $<

clean:
	rm $(OBJECTS)
	rm *.exe
