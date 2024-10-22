# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 14:24:16 by maustel           #+#    #+#              #
#    Updated: 2024/10/22 13:44:02 by maustel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = exec
CFLAGS = -Wall -Werror -Wextra -g
CFILES = executor.c executor_utils.c find_path.c exec_free.c error_handling.c check_files.c redirections.c exec_pipe.c heredoc.c

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
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OFILES)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

#IF READLINE IS NOT INSTALLED INSTALL IT WITH MAKE COMMAND IN MAC
rl:
	@brew install readline

#IF READLINE IS NOT INSTALLED INSTALL IT WITH MAKE LINUX (LINUX ONLY)
linux: readline_linux_install $(NAME)

#COMMAND TO INSTALL READLINE ON LINUX
readline_linux_install:
	apt install libreadline-dev

.PHONY: all clean fclean re
