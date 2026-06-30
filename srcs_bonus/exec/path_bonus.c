/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static char	*try_dir(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (full && access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*search_path(t_env *env, char *cmd)
{
	char	**dirs;
	char	*path;
	char	*pathenv;
	int		i;

	pathenv = env_get(env, "PATH");
	if (!pathenv)
		return (NULL);
	dirs = ft_split(pathenv, ':');
	path = NULL;
	i = 0;
	while (dirs && dirs[i])
	{
		path = try_dir(dirs[i], cmd);
		if (path)
			break ;
		i++;
	}
	ft_free_array(dirs);
	return (path);
}

static int	check_direct(char *cmd, char **out)
{
	struct stat	st;

	if (stat(cmd, &st) != 0)
	{
		cmd_error(cmd, "No such file or directory");
		return (127);
	}
	if (S_ISDIR(st.st_mode))
	{
		cmd_error(cmd, "Is a directory");
		return (126);
	}
	if (access(cmd, X_OK) != 0)
	{
		cmd_error(cmd, "Permission denied");
		return (126);
	}
	*out = ft_strdup(cmd);
	return (0);
}

int	resolve_path(t_shell *sh, char *cmd, char **out)
{
	if (!cmd[0])
	{
		cmd_error(cmd, "command not found");
		return (127);
	}
	if (ft_strchr(cmd, '/'))
		return (check_direct(cmd, out));
	*out = search_path(sh->env, cmd);
	if (!*out)
	{
		cmd_error(cmd, "command not found");
		return (127);
	}
	return (0);
}
