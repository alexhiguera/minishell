/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	run_builtin(t_shell *sh, char **argv)
{
	if (!ft_strncmp(argv[0], "echo", 5))
		return (bi_echo(argv));
	if (!ft_strncmp(argv[0], "cd", 3))
		return (bi_cd(sh, argv));
	if (!ft_strncmp(argv[0], "pwd", 4))
		return (bi_pwd());
	if (!ft_strncmp(argv[0], "export", 7))
		return (bi_export(sh, argv));
	if (!ft_strncmp(argv[0], "unset", 6))
		return (bi_unset(sh, argv));
	if (!ft_strncmp(argv[0], "env", 4))
		return (bi_env(sh));
	return (bi_exit(sh, argv));
}
