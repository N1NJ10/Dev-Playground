CC = gcc
CFLAGS = -I./include -Wall
AR = ar
ARFLAGS = rcs

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib
BIN_DIR = bin

LIB_NAME = crypto
LIB_TARGET = $(LIB_DIR)/lib$(LIB_NAME).a
TARGET = $(BIN_DIR)/Smallencoder

MAIN_SRC = $(SRC_DIR)/main.c
LIB_SRCS = $(filter-out $(MAIN_SRC),$(wildcard $(SRC_DIR)/*.c))
LIB_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))
HEADERS = $(wildcard $(INC_DIR)/*.h)

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_TARGET): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(TARGET): $(MAIN_SRC) $(LIB_TARGET) $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@ -L./$(LIB_DIR) -l$(LIB_NAME)

$(OBJ_DIR) $(LIB_DIR) $(BIN_DIR):
	mkdir -p $@

$(LIB_OBJS): | $(OBJ_DIR)
$(LIB_TARGET): | $(LIB_DIR)
$(TARGET): | $(BIN_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o $(LIB_DIR)/*.a $(BIN_DIR)/*

.PHONY: all clean
