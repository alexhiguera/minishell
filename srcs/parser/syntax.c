/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redir(t_tok type)
{
	return (type == T_IN || type == T_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

static int	check_redir(t_token *t)
{
	if (!t->next)
		return (synerr("newline"));
	if (t->next->type != T_WORD)
		return (synerr(t->next->value));
	return (1);
}

static int	check_pipe(t_token *t)
{
	if (!t->next)
		return (synerr("|"));
	if (t->next->type == T_PIPE)
		return (synerr("|"));
	return (1);
}

int	syntax_check(t_token *toks)
{
	if (toks && toks->type == T_PIPE)
		return (synerr("|"));
	while (toks)
	{
		if (is_redir(toks->type) && !check_redir(toks))
			return (0);
		if (toks->type == T_PIPE && !check_pipe(toks))
			return (0);
		toks = toks->next;
	}
	return (1);
}
