/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	bi_exit(t_shell *sh, char **argv)
{
	int	code;

	ft_putendl_fd("exit", 2);
	if (argv[1] && !is_numeric(argv[1]))
	{
		cmd_error2("exit", argv[1], "numeric argument required");
		shell_exit(sh, 2);
	}
	if (argv[1] && argv[2])
	{
		cmd_error("exit", "too many arguments");
		return (1);
	}
	if (argv[1])
		code = ft_atoi(argv[1]);
	else
		code = sh->exit_status;
	shell_exit(sh, (unsigned char)code);
	return (0);
}
