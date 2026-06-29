/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cd_target(t_shell *sh, char **argv)
{
	char	*home;

	if (!argv[1])
	{
		home = env_get(sh->env, "HOME");
		if (!home)
			cmd_error("cd", "HOME not set");
		return (home);
	}
	return (argv[1]);
}

static void	update_pwd(t_shell *sh, char *old)
{
	char	cwd[4096];

	if (old[0])
		env_set(&sh->env, "OLDPWD", old);
	if (getcwd(cwd, sizeof(cwd)))
		env_set(&sh->env, "PWD", cwd);
}

int	bi_cd(t_shell *sh, char **argv)
{
	char	*target;
	char	old[4096];

	if (argv[1] && argv[2])
	{
		cmd_error("cd", "too many arguments");
		return (1);
	}
	target = cd_target(sh, argv);
	if (!target)
		return (1);
	if (!getcwd(old, sizeof(old)))
		old[0] = '\0';
	if (chdir(target) != 0)
	{
		cmd_error2("cd", target, strerror(errno));
		return (1);
	}
	update_pwd(sh, old);
	return (0);
}
