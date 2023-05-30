# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 13:14:18 by lfarias-          #+#    #+#              #
#    Updated: 2022/10/23 14:25:56 by lfarias-         ###   ########.fr        #
#    Updated: 2022/09/23 18:58:58 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -I$(INCLUDES)
SRCS		=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
				ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
				ft_isspace.c ft_ispunct.c ft_islower.c ft_isupper.c ft_iscntrl.c \
				ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
				ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
				ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
				ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
				ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
				ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
				ft_lstmap.c ft_lstnew.c ft_lstsize.c

GNL_SRCS	=	get_next_line.c get_next_line_utils.c
PF_DIR		=	./ft_printf/
PF_SRCS		=	ft_hexstr.c ft_printf.c ft_ptoa.c ft_utoa.c
PRINTF		= 	$(addprefix $(PF_DIR), $(PF_SRCS))

OBJS		=	$(SRCS:.c=.o)
GNL_OBJS	=	$(GNL_SRCS:.c=.o)
PF_OBJS		=	$(PRINTF:.c=.o)
BOBJS		=	$(BONUSES:.c=.o)
LIBFT		=	ar -rcs
INCLUDES	=	./ft_printf/

$(NAME): $(OBJS) $(GNL_OBJS) $(PF_OBJS)
	$(LIBFT) $(NAME) $(OBJS) $(GNL_OBJS) $(PF_OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS) $(GNL_OBJS) $(PF_OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:
	all clean fclean re 
