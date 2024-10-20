/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:21 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/18 14:41:38 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell_eichhoernchen.h"


void    check_for_dollar(t_list *table, char **env)
{
    t_shell     expand;
    t_command   *row;
    char        *pos_dollar;

    expand.tmp = table;
    while (expand.tmp != NULL)
    {
        row = (t_command*) expand.tmp->content;
        expand.i = 0;
        while(row->args[expand.i] != NULL)
        {
            expand.k = 0;
            while (row->args[expand.i][expand.k] != '\0')
            {
                if (row->args[expand.i][expand.k] == '\0')
                {
                    printf("TEST19\n");
                    break ;
                }
                if (row->args[expand.i][expand.k] == '$')
                {
                    pos_dollar = tmp_dollar(row, &expand);
                    get_expanded_2(pos_dollar, env, row, &expand);
                }
                if (pos_dollar)
		        {
                    free(pos_dollar);
                    pos_dollar = NULL;
                }
                if (!(row->args[expand.i][expand.k] == '$' && ft_isalnum(row->args[expand.i][expand.k + 1])))
		        {
                    printf("row->args[expand->i][k]: %c\n", row->args[expand.i][expand.k - 1]);
                    printf("TEST20\n");
                    expand.k++;
                }
            }
            
            // pos_dollar = ft_strchr(row->args[expand.i], '$'); // should search for $ in in pos_dollar
            // if (pos_dollar != NULL)
            // {
            //     get_expanded_2(pos_dollar, env, row, &expand);
            //     // pos dollar should be incremented
            // }
            expand.i++;
        }
        expand.tmp = expand.tmp->next;
    }
    // print_table(table);
}


t_list *expansion(t_list *table, char **env) // change to our env
{
    check_for_quotes(table, env); // cif there are no quotes go into check_for_dollar
    // exit(EXIT_SUCCESS);
    check_for_dollar(table, env);
    print_table(table);
    return (NULL);
}




// strange thing happes with aösdökd$öaksd
// --> don't have an anwser for it

// potential problem with $$HOME$$$PATH
// --> depends on how we are handling $$
// ---- solving ----
// instead of splitting with $ I could insert a ws before every $ and slpit with space
// then check if with ft_isalnum if the string in question is a variable or $ or $?
// if alnum remove the $ and compare with the envs

// potential problem with non existing variables such as $TEST
//  now in args** there are empty string stored
//  don't know if that is an issue or if the indexes need to be arranged properly again
// example bash: echo hallo $TEST $sa hallo"welt   "hallo
//       --> hallo hallowelt   hallo