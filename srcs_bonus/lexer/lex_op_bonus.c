/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_op_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static t_tok	redir_type(char *line, int i, int *len)
{
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

static t_tok	op_type(char *line, int i, int *len)
{
	*len = 1;
	if (line[i] == '(')
		return (T_LPAREN);
	if (line[i] == ')')
		return (T_RPAREN);
	if (line[i] == '&')
	{
		*len = 2;
		return (T_AND);
	}
	if (line[i] == '|')
	{
		if (line[i + 1] == '|')
			*len = 2;
		if (*len == 2)
			return (T_OR);
		return (T_PIPE);
	}
	return (redir_type(line, i, len));
}

int	add_operator(char *line, int *i, t_token **toks)
{
	t_token	*tok;
	t_tok	type;
	int		len;

	type = op_type(line, *i, &len);
	if (line[*i] == '&' && line[*i + 1] != '&')
		return (0);
	tok = token_new(ft_substr(line, *i, len), type);
	if (!tok)
		return (0);
	token_add_back(toks, tok);
	*i += len;
	return (1);
}
