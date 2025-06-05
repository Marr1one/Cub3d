CC = cc -g3
CFLAGS = -Wall -Wextra -Werror

NAME = Cub3d
OBJDIR = obj

MLX_PATH = ./minilibx-linux

SRC = $(shell find . -type f -name "*.c" -not -path "$(MLX_PATH)/*")

OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
LFLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz


all : mlx_compile $(NAME)

$(shell mkdir -p $(OBJDIR))

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS) $(CFLAGS)
	@echo "*----------------------*"
	@echo "\033[1;32mCompilation completed 🎉\033[0m"
	@echo "*----------------------*"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

mlx_compile:
	$(MAKE) -C $(MLX_PATH)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_PATH) clean

re: fclean all

.PHONY: clean fclean re mlx_compile