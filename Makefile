CC = gcc -Wall
CFLAGS = -I./includes

TARGET = 2108_2119
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Compilation Successful"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(TARGET).exe $(OBJS)
	@echo "Clean Successful"
