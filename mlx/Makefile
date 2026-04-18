# Makefile for MLX42

MLX_DIR = .
BUILD_DIR = build

all:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR) --config Release
	ar rcs libmlx42.a $(BUILD_DIR)/libmlx42.a
	ranlib libmlx42.a

clean:
	rm -rf $(BUILD_DIR) libmlx42.a

.PHONY: all clean