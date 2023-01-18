CC = g++

CPPFLAG = -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed

all:
	$(CC) $(CPPFLAG) *.cc

debug:
	$(CC) -g -std=c++17 -lpthread -Wl,--no-as-needed -g *.cc -o debug.out

clean:
	$(RM) *.out