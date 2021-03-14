# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/21 18:15:56 by dohelee           #+#    #+#              #
#    Updated: 2021/03/14 08:28:49 by dohelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 
CFLAGS = -g -O3 -Wall -Wextra -Werror

NORM = ~/.norminette/norminette.rb
NORM_FLAGS = -R CheckForbiddenSourceHeader

LIB_INC_DIR = /usr/lib

LIB_MLX_NAME = mlx
LIB_MLX_DIR = ./minilibx-linux

LIB_FT_NAME = ft
LIB_FT_DIR = ./libft

NAME = cub3D
SRCS_DIR = ./srcs
SRCS_NAME = cub3d.c \
			draw_floor_ceiling.c \
			draw_sprite.c \
			draw_wall.c \
			event.c \
			get_next_line.c \
			init.c \
			luminosity.c \
			parse_cub.c \
			parse_utils_1.c \
			parse_utils_2.c \
			math.c \
			param_check.c \
			raycast_utils.c \
			raycast.c \
			save_bmp.c \
			utils.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME)) 
OBJS = $(SRCS:.c=.o)
BONUS_DIR = ./bonus

$(SRCS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(SRCS_DIR) -c $^ -o $@

# $(BONUS_DIR)/%.o : $(BONUS_DIR)/%.c
# 	$(CC) $(CFLAGS) -I$(BONUS_DIR) -c $^ -o $@

$(NAME) : $(OBJS)
	$(MAKE) all -C $(LIB_FT_DIR)
	$(MAKE) all -C $(LIB_MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIB_MLX_DIR) -l$(LIB_MLX_NAME) -L$(LIB_FT_DIR) -l$(LIB_FT_NAME) -L$(LIB_INC_DIR) -lXext -lX11 -lm -lbsd -o $(NAME)

all	: $(NAME)

clean :
	$(MAKE) clean -C $(LIB_MLX_DIR)
	$(MAKE) clean -C $(LIB_FT_DIR)
	rm -f $(OBJS) *~ core *.core
	
fclean : clean
	rm -rf $(NAME)

re : fclean all

bonus :
	##### not yet

norm : 
	$(NORM) $(NORM_FLAGS) $(SRCS_DIR)/*.c $(SRCS_DIR)/*.h
	
.PHONY: all clean fclean re bonus norm