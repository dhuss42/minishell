
#include "minishell_eichhoernchen.h"

void	print_token(token *tok)
{
	char *token_str;

	token_str = NULL;
	if (tok->type == TOKEN_PIPE)
		token_str = "PIPE";
	else if (tok->type == TOKEN_REDIN)
		token_str = "REDIRECT IN";
	else if (tok->type == TOKEN_REDOUT)
		token_str = "REDIRECT OUT";
	else if (tok->type == TOKEN_HEREDOC)
		token_str = "HEREDOC";
	else if (tok->type == TOKEN_REDAPPEND)
		token_str = "REDIRECTION APPEND";
	else if (tok->type == TOKEN_SQUOTES)
		token_str = "SINGLE QUOTES";
	else if (tok->type == TOKEN_DQUOTES)
		token_str = "DOUBLE QUOTES";
	else if (tok->type == TOKEN_ENVVAR)
		token_str = "ENVIRONMENT VARIABLE";
	else if (tok->type == TOKEN_EXITSTATUS)
		token_str = "EXIT STATUS";
	else if (tok->type == TOKEN_ARGS)
		token_str = "ARGUMENTS";
	else if (tok->type == TOKEN_WORD)
		token_str = "WORD";
	printf("Token\n Type: %s\n Value: %s\n\n", token_str, tok->input);
}

// function prints the Token struct and its contents
//	checks the token_type and changes the value of token_str accordingly

void	print_token_list(t_list *list)
{
	t_list *current = list;

	while (current != NULL)
	{
		token *tok = (token *)(current->content);
		print_token(tok);
		current = current->next;
	}
}