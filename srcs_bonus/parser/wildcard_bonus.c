/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	wild_match(char *pat, char *str)
{
	if (*pat == '\0')
		return (*str == '\0');
	if (*pat == '*')
	{
		while (*pat == '*')
			pat++;
		if (*pat == '\0')
			return (1);
		while (*str)
		{
			if (wild_match(pat, str))
				return (1);
			str++;
		}
		return (0);
	}
	if (*str && *pat == *str)
		return (wild_match(pat + 1, str + 1));
	return (0);
}

static int	hidden_ok(char *pattern, char *name)
{
	return (!(name[0] == '.' && pattern[0] != '.'));
}

static void	sort_matches(char **arr, int n)
{
	int		i;
	int		j;
	size_t	len;
	char	*tmp;

	i = -1;
	while (++i < n - 1)
	{
		j = -1;
		while (++j < n - 1 - i)
		{
			len = ft_strlen(arr[j]);
			if (ft_strlen(arr[j + 1]) > len)
				len = ft_strlen(arr[j + 1]);
			if (ft_strncmp(arr[j], arr[j + 1], len + 1) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

static void	finish_wildcards(t_cmd *cmd, char **matches, int n, char *pattern)
{
	char	**new;
	int		i;

	if (n == 0)
		new = argv_add(cmd->argv, ft_strdup(pattern));
	else
	{
		sort_matches(matches, n);
		i = -1;
		new = cmd->argv;
		while (matches[++i])
			new = argv_add(new, ft_strdup(matches[i]));
	}
	if (new)
		cmd->argv = new;
	ft_free_array(matches);
}

void	add_wildcards(t_cmd *cmd, char *pattern)
{
	DIR				*dir;
	struct dirent	*e;
	char			**matches;
	int				n;

	matches = ft_calloc(1, sizeof(char *));
	n = 0;
	dir = opendir(".");
	if (dir)
	{
		e = readdir(dir);
		while (e)
		{
			if (hidden_ok(pattern, e->d_name) && wild_match(pattern, e->d_name))
			{
				matches = argv_add(matches, ft_strdup(e->d_name));
				n++;
			}
			e = readdir(dir);
		}
		closedir(dir);
	}
	finish_wildcards(cmd, matches, n, pattern);
}
