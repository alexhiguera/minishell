/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_tok	op_type(char *line, int i, int *len)
{
	*len = 1;
	if (line[i] == '|')
		return (T_PIPE);
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			*len = 2;
		if (*len == 2)
			return (T_HEREDOC);
		return (T_IN);
	}
	if (line[i + 1] == '>')
		*len = 2;
	if (*len == 2)
		return (T_APPEND);
	return (T_OUT);
}

int	add_operator(char *line, int *i, t_token **toks)
{
	t_token	*tok;
	t_tok	type;
	int		len;

	type = op_type(line, *i, &len);
	tok = token_new(ft_substr(line, *i, len), type);
	if (!tok)
		return (0);
	token_add_back(toks, tok);
	*i += len;
	return (1);
}
