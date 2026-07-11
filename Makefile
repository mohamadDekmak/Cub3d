NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

MLX_DIR		= minilibx-linux
MLX_INC		= -I$(MLX_DIR)
MLX_LIB		= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

INCS        = -Iincludes $(MLX_INC) -I$(LIBFT_DIR)

SRC_DIR		= src
SRCS = \
    $(SRC_DIR)/main.c \
	$(SRC_DIR)/utils/errors.c \
    $(SRC_DIR)/events/hooks.c \
    $(SRC_DIR)/parsing/parser.c \
    $(SRC_DIR)/parsing/parser_utils.c \
	

OBJ_DIR		= obj
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	
$(LIBFT):
	make -C $(LIBFT_DIR)
clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)


fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
