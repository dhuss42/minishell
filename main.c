/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:48:20 by maustel           #+#    #+#             */
/*   Updated: 2024/10/07 12:48:20 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int main (int argc, char **argv, char **envp)
{
	char *args[] = {"/bin/ls", "-la", NULL};

	t_mainstruct	*test;
	test
	// char *args[] = {"ls -la", NULL};
	// const char *name = "PATH";
    // const char *env_p = getenv(name);
    // if(env_p){
    //     printf("Your %s is %s\n", name, env_p);
    // }
	if (executor (envp, args))
		return (1);
	(void)argc;
	(void)argv;
	return (0);
}
