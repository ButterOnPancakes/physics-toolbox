CC = g++
CFLAGS = -W -Wall
LDFLAGS = -lSDL3

BIN_DIR = bin

$(BIN_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

SOURCES = $(shell find src -name "*.cpp")

OBJECTS = $(patsubst %.cpp,$(BIN_DIR)/%.o,$(SOURCES))

EXAMPLES = src/main.cpp
EX_BIN = $(patsubst %.cpp,$(BIN_DIR)/%, $(EXAMPLES))

$(EX_BIN): $(BIN_DIR)/%: $(BIN_DIR)/%.o $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: bin/src/main
	./bin/src/main

clean:
	rm -rf $(BIN_DIR)