
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
	int exit_code;
	int len;

	// call print_error function to retrive exit code
	exit_code = 106; // change here
	len = get_int_length(exit_code);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
	{
		//  print_error(errno, NULL);
		return (-1);
	}
	tmp = ft_itoa(exit_code);
	printf(RED"exit_code tmp: %s\n"WHITE, tmp);
	free(row->args[expand->i]);
	row->args[expand->i] = ft_strdup(tmp);
	if (!row->args[expand->i])
	{
		//  print_error(errno, NULL);
		return (-1);
	}
	if (tmp)
		free(tmp);
	return (0);
}