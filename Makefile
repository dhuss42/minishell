CC = cc
CFLAGS = -Wall -Werror -Wextra -g -MMD -MP
# -MMD tells compiler to generate dependency files excluding system headers (ex: string.h)
# -MP Creates phony targets for those headers, preventing errors if the headers are deleted.
LFLAGS = -lreadline
# for readline functions
# is a linking flag not a compiler flag
NAME = minishell
CFILES = minishell.c\
	minishell_utils.c\
	environment/shlvl.c\
	environment/get_env.c\
	lexer/lexer.c\
	lexer/insert_trim_ws.c\
	lexer/get_len.c\
	lexer/split_space_quotes.c\
	lexer/tokeniser.c\
	lexer/syntax_errors.c\
	lexer/helper_lexer.c\
	lexer/memory_lexer.c\
	parser/parser.c\
	parser/helper_parser.c\
	parser/populate_cmd.c\
	parser/create_table.c\
	parser/memory_parser.c\
	expansion/expansion.c\
	expansion/check_for_expansion.c\
	expansion/get_expanded.c\
	expansion/exit_code.c\
	expansion/compare_with_env.c\
	expansion/remove_quotes.c\
	expansion/helper_expansion.c\
	builtins/builtins.c\
	builtins/env.c\
	builtins/pwd.c\
	builtins/export.c\
	builtins/export_args.c\
	builtins/export_helpers.c\
	builtins/export_no_args.c\
	builtins/echo.c\
	builtins/echo_expanded.c\
	builtins/unset.c\
	builtins/cd.c\
	builtins/cd_pwd_handling.c\
	builtins/exit.c\
	errors/error_handling.c\
	errors/error_handling_utils.c\
	executor/check_files.c\
	executor/exec_free.c\
	executor/exec_pipe.c\
	executor/exec_free_child.c\
	executor/executor_utils.c\
	executor/executor.c\
	executor/find_path.c\
	executor/heredoc.c\
	executor/heredoc_utils.c\
	executor/heredoc_expansion.c\
	executor/redirections.c\
	signals/handle_signals.c\
	free_minishell.c\
	print_tokenlist.c\
	print_table.c

# take out functions later such as print_table.c, print_tokenlist.c, builtins/builtins.c

OFILES = $(CFILES:.c=.o)
DEPS = $(OFILES:.o=.d)
# look into again

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDES = -I $(LIBFT_DIR)

all: $(NAME) executor/tmp
#@echo "\033[32m minishell built successfully! \033[0m"
# problem with running make multiple times
# works when the echo message is deleted. Also affects libft

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OFILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(OFILES) $(LIBFT) $(LFLAGS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(LIBFT_INCLUDES) -c $< -o $@

executor/tmp:
	@mkdir -p $@

clean:
	@echo "\033[33m cleaning minishell files \033[0m"
	@rm -f $(OFILES) $(DEPS)
	@$(MAKE) -C $(LIBFT_DIR) clean
# -C changes directory to libft/

fclean:
	@echo "\033[33m fcleaning minishell \033[0m"
	@rm -f $(OFILES) $(DEPS)
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
# fclean triggers two messages from clean in libft

re:
	@echo "\033[35m re making... \033[0m"
	@$(MAKE) fclean
	@$(MAKE) all

-include $(DEPS)
# - make won't stop with an error if i it cannot find the DEPS files
# looks in the dependencies in the .d files
# if any header files listed there have been changed since the last build
# make knows which object files need to be recompiled
# if the files are missing (first time running make)
# - preffix allows for make to continue without throwing an error

.PHONY: all clean fclean re
