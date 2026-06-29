/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
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

static int	skip_spaces(char *line, int i)
{
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}

t_token	*lex(char *line)
{
	t_token	*toks;
	int		i;

	toks = NULL;
	i = 0;
	while (line[i])
	{
		i = skip_spaces(line, i);
		if (!line[i])
			break ;
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			if (!add_operator(line, &i, &toks))
				break ;
		}
		else if (!add_word(line, &i, &toks))
			break ;
	}
	if (line[i])
	{
		token_clear(&toks);
		return (NULL);
	}
	return (toks);
}
