CC = g++
CFLAGS = -O2
OBJECTS = io.o arithmetics.o multiplication_int.o multiplication_double.o derived.o householder.o qr_alg.o qr.o

%.exe : %.o
	$(CC) $(CFLAGS) $? -o $@

%.o : %.cpp
	ctags *.cpp *.hpp -R ; $(CC) $(CFLAGS) -c $<

clean:
	rm *.exe
