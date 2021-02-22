# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/24 13:59:39 by dohelee           #+#    #+#              #
#    Updated: 2021/01/25 23:18:07 by dohelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
AR = ar rcs

SRCS = ft_toupper.c ft_tolower.c ft_isprint.c ft_isdigit.c ft_isascii.c ft_isalpha.c ft_isalnum.c \
		ft_atoi.c ft_strncmp.c ft_strnstr.c ft_strlen.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_memcmp.c \
		ft_memchr.c ft_memcpy.c ft_memccpy.c ft_memset.c ft_bzero.c ft_strrchr.c ft_calloc.c ft_strdup.c \
		ft_memmove.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		ft_lstiter.c ft_lstmap.c 

OBJS = $(SRCS:.c=.o)
OBJS_BONUS= $(SRCS_BONUS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
	$(AR) $@ $^

bonus : $(OBJS) $(OBJS_BONUS)
	$(AR) $(NAME) $^

all: $(NAME)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
