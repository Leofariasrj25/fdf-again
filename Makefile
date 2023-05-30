# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 14:03:09 by lfarias-          #+#    #+#              #
#    Updated: 2022/11/05 14:57:36 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
LIBFT_DIR = ./libft/
MLX_DIR = ./mlx/
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
SRC = 	main.c \
		utils.c \
		app.c \
		app_input.c \
		draw.c \
		draw_utils.c \
		map_draw.c \
		map.c \
		map_utils.c \
		transformations.c \
		math_utils.c \
		render.c \
		render2.c \
		events.c \
		menu.c
SRC_OBJ = $(SRC:.c=.o)
BONUS_SRC =	main_bonus.c \
		utils_bonus.c \
		app_bonus.c \
		app_input_bonus.c \
		draw_bonus.c \
		draw_utils_bonus.c \
		map_draw_bonus.c \
		map_bonus.c \
		map_utils_bonus.c \
		transformations_bonus.c \
		transformations2_bonus.c \
		math_utils_bonus.c \
		render_bonus.c \
		render2_bonus.c \
		events_bonus.c \
		events2_bonus.c \
		mouse_events_bonus.c \
		menu_bonus.c
BONUS_DIR = ./bonus/
BONUS_FILES = $(addprefix $(BONUS_DIR), $(BONUS_SRC))
BONUS_OBJS = $(BONUS_FILES:.c=.o) 
	
$(NAME): $(SRC_OBJ)
	make -C $(LIBFT_DIR) libft.a
	make -C $(MLX_DIR) all
	cp $(MLX_DIR)/libmlx.dylib .
	$(CC) $(CFLAGS) $(SRC_OBJ) $(LDFLAGS) -o $(NAME)

all: $(NAME)
	
clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f libmlx.dylib
	rm -f $(SRC_OBJ)

fclean: clean
	rm -f $(LIBFT_DIR)/libft.a
	rm -f $(NAME)

re: fclean all

bonus: $(BONUS_OBJS)
	make -C $(LIBFT_DIR) libft.a
	make -C $(MLX_DIR) all
	cp $(MLX_DIR)/libmlx.dylib .
	$(CC) $(CFLAGS) $(BONUS_FILES) $(LDFLAGS) -o $(NAME)

bclean:
	rm -rf $(BONUS_OBJS)
