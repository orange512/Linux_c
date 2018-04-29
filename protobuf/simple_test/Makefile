SRC := $(wildcard *.cc)
OBJ := $(patsubst %.cc,%.o,$(SRC))
CC := g++
LIBS := -lprotobuf
########################
all:
	$(CC) $(SRC) -oout $(LIBS)



