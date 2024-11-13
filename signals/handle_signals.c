/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:33:15 by maustel           #+#    #+#             */
/*   Updated: 2024/11/13 09:33:15 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../executor.h"

/*-------------------------------------------------------------
Initialisation of the terminal
temporarily change the terminal behavior,specifically
disabling the echoing of control characters.
term.c_lflag &= ~ECHOCTL modifies the terminal attributes.
tcsetattr(0, TCSANOW, &term) applies the modified terminal attributes.
---------------------------------------------------------------*/
void	init_terminal(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) != 0)
		print_error(E_INIT_TERMINAL, NULL, PRINT);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &term) != 0)
		print_error(E_INIT_TERMINAL, NULL, PRINT);
}

void	handle_child_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		print_error(130, NULL, NOTPRINT);
	}
	return ;
}

/*-------------------------------------------------------------
Handle SIGINT (ctrl + C)
rl_replace_line("", 0) Clears the current command line input.
rl_on_new_line() Moves the cursor to the beginning of the next line.
rl_redisplay() Redraws the screen, updating the display to reflect
the current state of the command line.
---------------------------------------------------------------*/
void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		print_error(130, NULL, NOTPRINT);
	}
}

/*-------------------------------------------------------------
Ignoring SIGQUIT: By calling signal(SIGQUIT, SIG_IGN), the program
tells the system to ignore SIGQUIT signals. This means the program
won't respond to the QUIT character (usually Ctrl+) in the terminal.
---------------------------------------------------------------*/
void	handle_signals(int is_child)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	if (is_child)
	{
		sa_int.sa_handler = &handle_child_signal;
		sigemptyset(&sa_int.sa_mask);
		// sa.sa_flags = SA_RESTART;
		sa_int.sa_flags = 0;
		if (sigaction(SIGINT, &sa_int, NULL) < 0)
			return ;
		// if (sigaction(SIGQUIT, &sa, NULL) < 0)
		// 	return ;
	}
	else
	{
		sa_int.sa_handler = &handle_sig;
		sa_quit.sa_handler = SIG_IGN;
		sigemptyset(&sa_int.sa_mask);
		sigemptyset(&sa_quit.sa_mask);
		sa_int.sa_flags = 0;
		sa_quit.sa_flags = 0;
		if (sigaction(SIGINT, &sa_int, NULL) < 0)
			return ;
		if (sigaction(SIGQUIT, &sa_quit, NULL) < 0)
			return ;
	}
}
