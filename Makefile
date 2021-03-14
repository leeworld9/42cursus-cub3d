# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/21 18:15:56 by dohelee           #+#    #+#              #
#    Updated: 2021/03/15 02:48:17 by dohelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 
CFLAGS = -O3 -Wall -Wextra -Werror

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

BONUS_NAME = cub3D_bonus
BONUS_SRCS_DIR = ./bonus
BONUS_SRCS_NAME = cub3d_bonus.c \
			draw_floor_ceiling_bonus.c \
			draw_sprite_bonus.c \
			draw_wall_bonus.c \
			event_key_bonus.c \
			event_button_bonus.c \
			get_next_line_bonus.c \
			init_bonus.c \
			luminosity_bonus.c \
			parse_cub_bonus.c \
			parse_utils_1_bonus.c \
			parse_utils_2_bonus.c \
			math_bonus.c \
			param_check_bonus.c \
			raycast_utils_bonus.c \
			raycast_bonus.c \
			save_bmp_bonus.c \
			utils_bonus.c \
			draw_map_bonus.c
BONUS_SRCS = $(addprefix $(BONUS_SRCS_DIR)/, $(BONUS_SRCS_NAME)) 		
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

$(SRCS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(SRCS_DIR) -c $^ -o $@

$(BONUS_SRCS_DIR)/%.o : $(BONUS_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(BONUS_SRCS_DIR) -c $^ -o $@

$(NAME) : $(OBJS)
	$(MAKE) all -C $(LIB_FT_DIR)
	$(MAKE) all -C $(LIB_MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIB_MLX_DIR) -l$(LIB_MLX_NAME) -L$(LIB_FT_DIR) -l$(LIB_FT_NAME) -L$(LIB_INC_DIR) -lXext -lX11 -lm -lbsd -o $(NAME)

$(BONUS_NAME) : $(BONUS_OBJS)
	$(MAKE) all -C $(LIB_FT_DIR)
	$(MAKE) all -C $(LIB_MLX_DIR)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -L$(LIB_MLX_DIR) -l$(LIB_MLX_NAME) -L$(LIB_FT_DIR) -l$(LIB_FT_NAME) -L$(LIB_INC_DIR) -lXext -lX11 -lm -lbsd -o $(BONUS_NAME)

all	: $(NAME) $(BONUS_NAME)

bonus : $(BONUS_NAME)

clean :
	$(MAKE) clean -C $(LIB_MLX_DIR)
	$(MAKE) clean -C $(LIB_FT_DIR)
	rm -f $(OBJS) *~ core *.core
	rm -f $(BONUS_OBJS) *~ core *.core
	
fclean : clean
	rm -rf $(NAME)
	rm -rf $(BONUS_NAME)

re : fclean all

norm : 
	$(NORM) $(NORM_FLAGS) $(SRCS_DIR)/*.c $(SRCS_DIR)/*.h

bonus_norm :
	$(NORM) $(NORM_FLAGS) $(BONUS_SRCS_DIR)/*.c $(BONUS_SRCS_DIR)/*.h
	
.PHONY: all clean fclean re bonus norm