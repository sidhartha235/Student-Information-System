CC = gcc
CFLAGS = -I./includes

TARGET = 2108_2119

SRC = $(wildcard src/*.c)

all : $(TARGET)

$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@echo "Compilation Successful"

clean:
	rm -f $(TARGET)
	@echo "Clean Successful"
