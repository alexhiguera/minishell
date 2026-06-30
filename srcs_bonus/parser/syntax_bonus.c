/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	is_redir(t_tok type)
{
	return (type == T_IN || type == T_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

static int	is_binop(t_tok type)
{
	return (type == T_PIPE || type == T_AND || type == T_OR);
}

static int	is_cmd_start(t_tok type)
{
	return (type == T_WORD || is_redir(type) || type == T_LPAREN);
}

static int	valid_adjacency(t_token *prev, t_token *cur)
{
	if (!prev)
		return (is_cmd_start(cur->type));
	if (is_redir(prev->type))
		return (cur->type == T_WORD);
	if (is_binop(prev->type) || prev->type == T_LPAREN)
		return (is_cmd_start(cur->type));
	if (prev->type == T_RPAREN)
		return (is_binop(cur->type) || is_redir(cur->type)
			|| cur->type == T_RPAREN);
	return (is_binop(cur->type) || is_redir(cur->type)
		|| cur->type == T_RPAREN || cur->type == T_WORD);
}

int	syntax_check(t_token *toks)
{
	t_token	*prev;
	int		depth;

	prev = NULL;
	depth = 0;
	while (toks)
	{
		depth += (toks->type == T_LPAREN) - (toks->type == T_RPAREN);
		if (depth < 0)
			return (synerr(")"));
		if (!valid_adjacency(prev, toks))
			return (synerr(toks->value));
		prev = toks;
		toks = toks->next;
	}
	if (depth != 0 || !prev || is_binop(prev->type)
		|| is_redir(prev->type) || prev->type == T_LPAREN)
		return (synerr("newline"));
	return (1);
}
