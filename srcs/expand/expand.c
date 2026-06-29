/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_str(t_shell *sh, char *raw)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (raw[i] && res)
	{
		if (raw[i] == '\'')
			res = app_single(res, raw, &i);
		else if (raw[i] == '"')
			res = app_double(sh, res, raw, &i);
		else if (raw[i] == '$')
			res = app_dollar(sh, res, raw, &i);
		else
			res = app_char(res, raw[i++]);
	}
	return (res);
}

char	*expand_vars(t_shell *sh, char *line)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (line[i] && res)
	{
		if (line[i] == '$')
			res = app_dollar(sh, res, line, &i);
		else
			res = app_char(res, line[i++]);
	}
	return (res);
}

void	expand_tokens(t_shell *sh, t_token *toks)
{
	t_token	*prev;

	prev = NULL;
	while (toks)
	{
		if (toks->type == T_WORD && prev && prev->type == T_HEREDOC)
			replace_val(&toks->value, strip_quotes(toks->value));
		else if (toks->type == T_WORD)
			replace_val(&toks->value, expand_str(sh, toks->value));
		prev = toks;
		toks = toks->next;
	}
}
