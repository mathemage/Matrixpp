CC = g++
CFLAGS = -O2
OBJECTS = io.o arithmetics.o multiplication_int.o multiplication_double.o qr.o derived.o householder.o

%.exe : %.o
	$(CC) $(CFLAGS) $? -o $@

%.o : %.cpp
	ctags *.cpp *.hpp -R ; $(CC) $(CFLAGS) -c $<

clean:
	rm *.exe
