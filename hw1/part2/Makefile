C = g++
CFLAGS = -g -Wall
DFLAGS = -DDEBUG
SRC = main.cpp sorts.cpp 
OBJ = main.o sorts.o
TARGET = test-me

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(DFLAGS) -o $@ $(OBJ)

.c.o: 
	$(CC) $(CFLAGS) $(DFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJ)
