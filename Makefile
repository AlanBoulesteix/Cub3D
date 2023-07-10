

NAME 			:= cub3d	

SRC_DIR			= src/
INCLUDES_DIR	= includes/

FILES			:= get_next_line.c \
				get_next_line_utils.c \
				parsing.c \
				read_file.c \


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

##################################################################

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME) $(LIBFT)

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