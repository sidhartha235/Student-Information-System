CC = gcc -Wall

CLIENT_INCLUDE_DIR = includes/client 
SERVER_INCLUDE_DIR = includes/server 
COMMON_INCLUDE_DIR = includes/common

CLIENT_INCLUDES = -I./$(CLIENT_INCLUDE_DIR) -I./$(COMMON_INCLUDE_DIR)
SERVER_INCLUDES = -I./$(SERVER_INCLUDE_DIR) -I./$(COMMON_INCLUDE_DIR)

SERVER_TARGET = server_08_19
CLIENT_TARGET = client_08_19

SERVER_SRCS = $(wildcard src/server/*.c) $(wildcard src/common/*.c)
CLIENT_SRCS = $(wildcard src/client/*.c) $(wildcard src/common/*.c)

SERVER_OBJS = $(SERVER_SRCS:%.c=%.o) 
CLIENT_OBJS = $(CLIENT_SRCS:%.c=%.o)

all: $(CLIENT_TARGET) $(SERVER_TARGET)
# all : $(CLIENT_TARGET)
# all : $(SERVER_TARGET)

$(SERVER_TARGET): $(SERVER_OBJS) 
	$(CC) -o $@ $^
	@echo "Server compilation successful"

$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CC) -o $@ $^
	@echo "Client compilation successful"

%.o: %.c
	$(CC) $(if $(findstring src/server,$<),$(SERVER_INCLUDES),$(CLIENT_INCLUDES)) -c $< -o $@

clean:
	rm -f $(CLIENT_TARGET) $(SERVER_TARGET) $(SERVER_OBJS) $(CLIENT_OBJS)
	@echo "Clean succesful"