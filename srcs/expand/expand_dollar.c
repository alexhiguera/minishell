/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_name_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static int	is_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*app_status(t_shell *sh, char *res, int *i)
{
	char	*num;

	(*i)++;
	num = ft_itoa(sh->exit_status);
	res = gc_strjoin(res, num);
	free(num);
	return (res);
}

char	*app_dollar(t_shell *sh, char *res, char *raw, int *i)
{
	char	*name;
	char	*val;
	int		start;

	(*i)++;
	if (raw[*i] == '?')
		return (app_status(sh, res, i));
	if (!is_name_start(raw[*i]))
		return (app_char(res, '$'));
	start = *i;
	while (is_name_char(raw[*i]))
		(*i)++;
	name = ft_substr(raw, start, *i - start);
	val = env_get(sh->env, name);
	free(name);
	if (val)
		return (gc_strjoin(res, val));
	return (res);
}
