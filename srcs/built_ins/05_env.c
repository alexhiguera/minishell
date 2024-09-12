/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:10:04 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 12:39:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char *input, char **envp)
{
	(void)input;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (1);
}
