/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:09:54 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 12:39:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char *input, char **envp)
{
	char	*pwd;

	(void)envp;
	(void)input;
	pwd = getenv("PWD");
	if (pwd)
		printf("%s\n", pwd);
	else
		printf("\n");
	return (1);
}
