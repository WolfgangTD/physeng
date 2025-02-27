CC = g++
CFLAGS = -Iinclude/
LDFLAGS = -Llib/ -lSDL3
TARGET = PhyseEng
SRC = main.cpp

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
