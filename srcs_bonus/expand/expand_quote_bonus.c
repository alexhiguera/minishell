/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	*app_single(char *res, char *raw, int *i)
{
	int	start;

	start = ++(*i);
	while (raw[*i] && raw[*i] != '\'')
		(*i)++;
	res = str_append_n(res, raw + start, *i - start);
	if (raw[*i])
		(*i)++;
	return (res);
}

char	*app_double(t_shell *sh, char *res, char *raw, int *i)
{
	(*i)++;
	while (raw[*i] && raw[*i] != '"')
	{
		if (raw[*i] == '$')
			res = app_dollar(sh, res, raw, i);
		else
			res = app_char(res, raw[(*i)++]);
		if (!res)
			return (NULL);
	}
	if (raw[*i])
		(*i)++;
	return (res);
}
