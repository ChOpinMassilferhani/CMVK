CC = g++

CPPFLAG = -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed

all:
	$(CC) $(CPPFLAG) *.cc


clean:
	$(RM) *.out