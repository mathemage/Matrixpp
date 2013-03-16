CC = g++
CFLAGS = -O2
OBJECTS = io.o arithmetics.o multiplication.o qr.o derived.o

%.exe : %.o
	$(CC) $(CFLAGS) $? -o $@

%.o : %.cpp
	ctags *.cpp *.hpp -R ; $(CC) $(CFLAGS) -c $<

clean:
	rm *.exe
