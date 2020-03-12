# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/18 15:43:22 by mminet            #+#    #+#              #
#    Updated: 2020/03/06 19:35:55 by mminet           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

LIBFT = ./libft/libft.a

FLAGS = gcc -Wall -Wextra -Werror
INCLUDES = -L mlx/ -lmlx -framework OpenGL -framework AppKit
HEADERS = cub3d.h

SRC = 	cub3d.c\
		draw.c\
		events.c\
		ft_exit.c\
		get_next_line.c\
		map.c\
		move.c\
		parse.c\
		parse2.c\
		ray_casting.c\
		ray_casting2.c\
		save.c\
		sprite.c\

OBJ = $(patsubst %.c, obj/%.o, $(SRC))

MLX = ./mlx/libmlx.a
HEADERS = cub3d.h

all: $(NAME)

$(OBJ): ${HEADERS}

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@echo "\n==> Making Cub3D"
	$(FLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@echo "\n==> Making LIBFT"
	make -C ./libft

libft/%.o: libft/%.c
	$(FLAGS) -c $< -o $@

obj/%.o: %.c
	mkdir -p obj
	$(FLAGS) -c $< -o $@

run: $(NAME)
	@echo "\n==> Running Cub3d"
	@./$(NAME) map.cub

runs: $(NAME)
	@echo "\n==> Running Cub3d with --save arg"
	@./$(NAME) map.cub --save

$(MLX):
	@echo "\n==> Making MLX"
	make -C ./mlx

norme:
	norminette *.c *.h

clean:
	rm -rf obj
	rm -rf img.bmp
	make -C ./libft clean

fclean: clean
	rm -rf $(NAME) *.dSYM $(LIBFT)
	make -C ./mlx clean
	make -C ./libft fclean

re: fclean all
rerun: re run
