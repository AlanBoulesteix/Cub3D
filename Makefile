# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 13:51:05 by aboulest          #+#    #+#              #
#    Updated: 2023/07/13 13:03:16 by aboulest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 			:= cub3d	

SRC_DIR			= src/
INCLUDES_DIR	= includes/

FILES			:= main.c \
				get_next_line.c \
				get_next_line_utils.c \
				str_utils.c \
				parsing.c \
				data.c \
				read_file_utils.c \
				read_file.c \
				game.c \


SRC				= $(addprefix $(SRC_DIR), $(FILES))

OBJ_DIR			= .build/
OBJ				= $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

LIBFT			= lib/libft/libft.a
MAKE_LIBFT		= make -C lib/libft/

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3 -pthread
INCLUDES		= -I$(INCLUDES_DIR) -Ilib/libft/ -I$(INCLUDES_DIR)cub3d -I$(INCLUDES_DIR)get_next_line

RM				= rm -f
DIR_DUP			= mkdir $(OBJ_DIR)
DIR_DUPS		= mkdir $(OBJ_DIR)$(SRC_DIR)


MLX			= -Imlx_linux -O3
MAKE_MLX	= make  -C minilibx-linux
MLX_CC		= -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

##################################################################

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(MAKE_MLX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(MLX_CC) -o $(NAME) $(LIBFT)

$(OBJ_DIR)%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	$(DIR_DUP)
	$(DIR_DUPS)

$(LIBFT):
	${MAKE_LIBFT}

clean: 
	make clean -C lib/libft
	$(RM) $(OBJ)
	rmdir $(OBJ_DIR)$(SRC_DIR)
	rmdir $(OBJ_DIR)

fclean: clean
	make fclean -C lib/libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re