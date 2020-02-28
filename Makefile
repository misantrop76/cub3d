# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/18 15:43:22 by mminet            #+#    #+#              #
#    Updated: 2020/02/25 21:12:01 by mminet           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


NAME = Cub3D

LIBFT = ./libft/libft.a
LIBFT_SRC := $(wildcard libft/*.c)
LIBFT_OBJ := $(patsubst libft/%.c, libft/%.o, $(LIBFT_SRC))

FLAGS = gcc -Wall -Wextra -Werror
INCLUDES = -L mlx/ -lmlx -framework OpenGL -framework AppKit
HEADERS = cub3d.h

SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, obj/%.o, $(SRC))

MLX = ./mlx/libmlx.a
HEADERS = cub3d.h

all: $(NAME)

$(OBJ): ${HEADERS}

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@echo "\n==> Making Cub3D"
	$(FLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT): $(LIBFT_OBJ)
	@echo "\n==> Making LIBFT"
	ar rcs $(LIBFT) $(LIBFT_OBJ)

libft/%.o: libft/%.c
	$(FLAGS) -c $< -o $@

obj/%.o: %.c
	mkdir -p obj
	$(FLAGS) -c $< -o $@

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
	rm -rf libft/*.o obj
	rm -rf img.bmp

fclean: clean
	rm -rf $(NAME) *.dSYM $(LIBFT)
	make -C ./mlx clean

re: fclean all
rerun: re run
