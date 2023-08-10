CC := gcc
CFLAGS := -Wall -std=c11

EXTRA_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
$(eval $(EXTRA_ARGS):;@:)

PART := $(firstword $(EXTRA_ARGS))
EXTRA_ARGS := $(wordlist 2,$(words $(EXTRA_ARGS)), $(EXTRA_ARGS))

BUILD_DIR := ./.build
SRC_DIR := ./src

TARGET_EXEC := $(BUILD_DIR)/$(PART).out
OBJ := $(BUILD_DIR)/$(PART).o
SRC := $(SRC_DIR)/$(PART).c

$(TARGET_EXEC): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ): $(SRC)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

build: $(TARGET_EXEC)

run: build
	@$(TARGET_EXEC) $(EXTRA_ARGS)

.PHONY: clean
clean:
	@rm -r $(BUILD_DIR)
