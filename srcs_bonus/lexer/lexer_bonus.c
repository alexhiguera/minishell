/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

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

static int	is_op_char(char c)
{
	return (c == '|' || c == '<' || c == '>'
		|| c == '(' || c == ')' || c == '&');
}

static void	*lex_fail(t_token **toks)
{
	token_clear(toks);
	return (NULL);
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
		if (is_op_char(line[i]))
		{
			if (!add_operator(line, &i, &toks))
				return (lex_fail(&toks));
		}
		else if (!add_word(line, &i, &toks))
			return (lex_fail(&toks));
	}
	return (toks);
}
