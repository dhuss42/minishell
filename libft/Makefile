# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maustel <maustel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 13:29:28 by maustel           #+#    #+#              #
#    Updated: 2023/10/25 17:02:26 by maustel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
	ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
	ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c\
	ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
	ft_lstclear.c ft_lstiter.c ft_lstmap.c

#.c=.o substitution reference. Replaces .c with .o
#OBJS	= $(SRCS:.c=.o) -> assigns list of obj files to OBJS

OBJS	= $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all:	$(NAME)

#%.o: %.c tells make that each .o file depends on a .c file with the same name.
#if .o is out of date,  make will execute the recipe for the %.o: %.c
#Generate object file from a c source file (%.o target, %.c prereqisite)
# The % is a wildcard that matches any string of characters.
#-c is a flag that tells the compiler to generate an object file.
#-o is a flag that tells the compiler what to name the output file.
#$< and $@ are automatic variables. (predefined) $< represents the first
# dependency (in this case the .c file), $@ represents the target (.o file)
%.o: %.c
	cc $(FLAGS) -c $< -o $@

#Creats a library named $(NAME) from the object files specified by $(OBJS)
#replacing any existing files in the library with the same names, and
#writing an index into the library (s);
#r: insert the specified files into the archive
#c create archive, if not exist
#$(NAME): $(OBJS) is the rule. It says that to make a file with the name stored in
#NAME, you need the files listed in OBJS.
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:	$(OBJS) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

#phony says that the following targets do not correspond to actual files
.PHONY:			all clean fclean re bonus
