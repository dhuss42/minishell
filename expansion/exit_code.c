
#include "../minishell_eichhoernchen.h"

int	get_int_length(int num)
{
	int len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

int	get_exit_code(char *tmp, t_command *row, t_shell *expand)
{
	char *tmp_ec;
	int exit_code;
	int len;
	int	index;

	tmp_ec = NULL;
	index = 0;
	// exit_code = print_error(0, NULL);
	exit_code = 106; // change here
	len = get_int_length(exit_code);
	tmp_ec = malloc(sizeof(char) * (len + 1));
	if (!tmp_ec)
	{
		//  print_error(errno, NULL);
		return (-1);
	}
	len += ft_strlen(row->args[expand->i]) - 2;
	// + len from the entire string - 2 ($?)
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
	{
		free(tmp_ec);
		//  print_error(errno, NULL);
		return (-1);
	}
	printf("[%zu]expand->k: %c\n", expand->k, row->args[expand->i][expand->k]);
	len = 0;
	expand->j = 0;
	while (expand->j < expand->k)
		tmp[len++] = row->args[expand->i][expand->j++];
	expand->j += 2;
	printf(MAGENTA"tmp before exit code: %s\n"WHITE, tmp);

	tmp_ec = ft_itoa(exit_code);
	expand->k += ft_strlen(tmp_ec);
	printf(RED"exit_code tmp_ec: %s\n"WHITE, tmp_ec);

	while(tmp_ec[index] != '\0')
		tmp[len++] = tmp_ec[index++];
	printf(MAGENTA"tmp after copying exitcode: %s\n"WHITE, tmp);
	if (tmp_ec)
		free(tmp_ec);

	while (row->args[expand->i][expand->j] != '\0')
		tmp[len++] = row->args[expand->i][expand->j++];
	printf(MAGENTA"tmp after copying remainder: %s\n"WHITE, tmp);
	tmp[len] = '\0';
	if (row->args[expand->i])
		free(row->args[expand->i]);
	row->args[expand->i] = ft_strdup(tmp);
	if (!row->args[expand->i])
	{
		free(tmp);
		//  print_error(errno, NULL);
		return (-1);
	}
	printf("tmp: %s\n", tmp);
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	// move expand->k accordingly
	return (0);
}

// needs to be split into multiple functions