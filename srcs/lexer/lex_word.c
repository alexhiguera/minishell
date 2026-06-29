/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	skip_quote(char *line, int i)
{
	char	quote;

	quote = line[i++];
	while (line[i] && line[i] != quote)
		i++;
	if (!line[i])
		return (-1);
	return (i + 1);
}

int	add_word(char *line, int *i, t_token **toks)
{
	int		start;
	int		quoted;
	t_token	*tok;

	start = *i;
	quoted = 0;
	while (line[*i] && !is_space(line[*i]) && !is_meta(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quoted = 1;
			*i = skip_quote(line, *i);
			if (*i == -1)
				return (0);
		}
		else
			(*i)++;
	}
	tok = token_new(ft_substr(line, start, *i - start), T_WORD);
	if (!tok)
		return (0);
	tok->quoted = quoted;
	token_add_back(toks, tok);
	return (1);
}
