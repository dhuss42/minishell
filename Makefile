# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 14:24:16 by maustel           #+#    #+#              #
#    Updated: 2024/10/10 12:38:31 by maustel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = exec
CFLAGS = -Wall #-Werror -Wextra -g
CFILES = executor.c find_path.c exec_free.c error_handling.c check_files_red.c redirections.c

OFILES = $(CFILES:.c=.o)

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDES = -I $(LIBFT_DIR)

INCLUDES = $(LIBFT_INCLUDES)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OFILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OFILES)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
