/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:06:00 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 15:39:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtin(char *input, char **envp)
{
	int	idx;

	ft_exit_check(input);
	idx = 0;
	while (input[idx])
	{
		if (input[idx] == '|' || input[idx] == '<' || input[idx] == '>')
			return (0);
		idx++;
	}
	if (ft_strncmp(input, "echo", 4) == 0)
		return (ft_echo(input));
	else if (ft_strncmp(input, "cd", 2) == 0)
		return (ft_cd(input));
	else if (ft_strncmp(input, "export", 6) == 0)
		return (ft_export(input, envp));
	else if (ft_strncmp(input, "unset", 5) == 0)
		return (ft_unset(input, envp, idx));
	else if (ft_strncmp(input, "pwd", 3) == 0)
		return (ft_pwd(input, envp));
	else if (ft_strncmp(input, "env", 3) == 0)
		return (ft_env(input, envp));
	return (0);
}

void	ft_exit_check(char *input)
{
	int	len;
	int	num;

	num = 0;
	len = 0;
	while (input[len])
		len++;
	if (len == 4 && ft_strncmp(input, "exit", 4) == 0)
		exit (1);
	else if (len > 4 && ft_strncmp(input, "exit ", 5) == 0)
	{
		num = ft_exit_num(input);
		exit(num);
	}
}

int	ft_exit_num(char *input)
{
	char	numstr[3];
	int		idx;
	int		idy;

	idx = 4;
	idy = 0;
	while (input[idx])
	{
		if (input[idx] > '0' && input[idx] < '9')
			numstr[idy++] = input[idx];
		idx++;
	}
	numstr[idy] = '\0';
	return (ft_atoi(numstr));
}
