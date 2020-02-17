# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2020/01/30 19:33:08 by mminet       #+#   ##    ##    #+#        #
#    Updated: 2020/02/13 18:01:23 by mminet      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = Cub3D

LIBFT = ./libft/libft.a
LIBFT_SRC := $(wildcard libft/*.c)
LIBFT_OBJ := $(patsubst libft/%.c, libft/%.o, $(LIBFT_SRC))

FLAGS = gcc -g3
INCLUDES = -L mlx/ -lmlx -framework OpenGL -framework AppKit

SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, obj/%.o, $(SRC))

MLX = ./mlx/libmlx.a
HEADERS = cub3d.h

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@echo "\n==> Making Cub3D"
	$(FLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT): $(LIBFT_OBJ)
	@echo "\n==> Making LIBFT"
	ar rcs $(LIBFT) $(LIBFT_OBJ)

libft/%.o: libft/%.c
	$(FLAGS) -Iincludes -c $< -o $@

obj/%.o: %.c
	mkdir -p obj
	$(FLAGS) -Iincludes -c $< -o $@

run: $(NAME)
	@echo "\n==> Running Cub3d"
	@./$(NAME) map.cub

runs: $(NAME)
	@echo "\n==> Running Cub3d with -save arg"
	@./$(NAME) map.cub -save

$(MLX):
	@echo "\n==> Making MLX"
	make -C ./mlx

norme:
	norminette *.c *.h

clean:
	rm -rf libft/*.o obj/* mlx/*.o
	rm -rf screenshot.bmp

fclean: clean
	rm -rf $(NAME) *.dSYM $(LIBFT)
	make -C ./mlx clean

re: fclean all
rerun: re run
