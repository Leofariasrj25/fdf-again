# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :::      :::    :::     #
#                                                     +:+  +:+       ++       #
#    By: lfarias- <lfarias-@student.42.rio>         #+#    #+#              #
#                                                 #+#   #+#   #+#            #
#    Created: 2022/09/14 14:03:09 by lfarias-          #+#    #+#             #
#    Updated: 2026/04/17 by lfarias-                 ###    ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -I./mlx/include -I./libft/
LIBFT_DIR = ./libft/
MLX_DIR = ./mlx/
LDFLAGS = -L$(LIBFT_DIR) -L$(MLX_DIR)/build -L$(MLX_DIR)/build/_deps/glfw-build/src -lft -lmlx42 -lglfw3 -lOpenGL -lpthread -lm -ldl -lX11

SRC = 	bonus/main_bonus.c \
		bonus/utils_bonus.c \
		bonus/app_bonus.c \
		bonus/app_input_bonus.c \
		bonus/draw_bonus.c \
		bonus/draw_utils_bonus.c \
		bonus/map_draw_bonus.c \
		bonus/map_bonus.c \
		bonus/map_utils_bonus.c \
		bonus/transformations_bonus.c \
		bonus/transformations2_bonus.c \
		bonus/math_utils_bonus.c \
		bonus/render_bonus.c \
		bonus/render2_bonus.c \
		bonus/events_bonus.c \
		bonus/events2_bonus.c \
		bonus/mouse_events_bonus.c \
		bonus/menu_bonus.c
SRC_OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC_OBJ)
	make -C $(LIBFT_DIR) libft.a
	make -C $(MLX_DIR) all
	$(CC) $(CFLAGS) $(SRC_OBJ) -o $(NAME) $(LDFLAGS)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f $(SRC_OBJ)

fclean: clean
	rm -f $(LIBFT_DIR)/libft.a
	rm -f $(NAME)

re: fclean all

# Run all tests
test: tests/test_input tests/test_map tests/test_color tests/test_math
	@echo ""
	@echo "========================================"
	@echo "Running all tests..."
	@echo "========================================"
	@echo ""
	@./tests/test_input
	@./tests/test_map
	@./tests/test_color
	@./tests/test_math
	@echo ""
	@echo "To run specific tests:"
	@echo "  make test-input    # Input validation"
	@echo "  make test-map     # Map parsing"
	@echo "  make test-color  # Color conversion"
	@echo "  make test-math   # Math utilities"
	@echo ""

# Run individual test categories
test-input: tests/test_input
	@./tests/test_input

test-map: tests/test_map
	@./tests/test_map

test-color: tests/test_color
	@./tests/test_color

test-math: tests/test_math
	@./tests/test_math

# List available tests
test-list:
	@echo "Available tests:"
	@echo "  input   - Input validation (22 tests)"
	@echo "  map     - Map parsing (20 tests)"
	@echo "  color   - Color conversion (12 tests)"
	@echo "  math    - Math utilities (36 tests)"
	@echo ""
	@echo "Run: make test        # Run all (90 tests)"
	@echo "Run: make test-math  # Run math only"

tests/test_input: tests/test_input.c
	cc -Wall -Wextra -Werror tests/test_input.c -o tests/test_input

tests/test_map: tests/test_map.c
	cc -Wall -Wextra -Werror tests/test_map.c -o tests/test_map

tests/test_color: tests/test_color.c
	cc -Wall -Wextra -Werror tests/test_color.c -o tests/test_color

tests/test_math: tests/test_math.c
	cc -Wall -Wextra -Werror tests/test_math.c -o tests/test_math -lm