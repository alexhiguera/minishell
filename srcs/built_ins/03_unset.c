/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:09:41 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 15:39:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_unset(char *input, char **envp, int len)
{
    char    **splt_input;
    char    *var;

    if (len == 5 || len == 6)
        return (1);
    splt_input = ft_split(input, ' ');
    var = splt_input[1];
    while (*envp)
    {
        if (ft_strncmp(*envp, var, strlen(var)) == 0)
        {
            while (*envp)
            {
                *envp = *(envp + 1);
                envp++;
            }
            break ;
        }
        envp++;
    }
    ft_free_spltinput(splt_input);
    return (1);
}
