NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

MLX_DIR		= minilibx-linux
MLX_INC		= -I$(MLX_DIR)
MLX_LIB		= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

INCS		= -Iincludes $(MLX_INC)

SRC_DIR		= src
SRCS		= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/events/hooks.c \
	$(SRC_DIR)/utils/errors.c

OBJ_DIR		= obj
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
