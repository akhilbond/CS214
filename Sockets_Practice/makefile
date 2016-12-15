CC=gcc
ARGS=-c
LIBS=-pthread
EXE=libnet.out
TEST_EXE=temp.out
DEBUG_EXE=debug.out
EXE_ARGS=

all: libnet

clean:
	rm -rf  *.o *.gch *.bin $(EXE) $(TEST_EXE)

debug_client: temp_debug

debug_server: temp_server

test: temp_run

test_debug: clean clr
	$(CC) -g $(LIBS) -o $(DEBUG_EXE) libnetfiles.c test_files.c
	gdb -ex run ./$(DEBUG_EXE)

test_server: libnetfiles.o libnetserver.o
	$(CC) -g $(LIBS) -o server_temp.out netfileserver.o libnetfiles.o
	gdb server_temp.out

test_run: clean	clr libnet
	$(CC) $(LIBS) -o $(TEST_EXE) libnetfiles.o test_files.o
	./$(TEST_EXE)

clr:
	clear

server: clean libnetserver.o
	$(CC) $(LIBS) -o server.out netfileserver.o libnetfiles.o
	./server.out

libnet: clr clr netfileserver.o libnetfiles.o temp_files.o
	$(CC) $(LIBS) -o $(TEST_EXE) libnetfiles.o temp_files.o


libnetserver.o: libnetfiles.o
	$(CC) $(ARGS) netfileserver.c

libnetfiles.o:
	$(CC) $(ARGS) libnetfiles.c

test_files.o:
	$(CC) $(ARGS) temp_files.c
