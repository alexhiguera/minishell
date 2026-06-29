/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*new_pipe_segment(t_cmd *cur)
{
	cur->next = cmd_new();
	return (cur->next);
}

t_cmd	*parse(t_token *toks)
{
	t_cmd	*cmds;
	t_cmd	*cur;

	if (!syntax_check(toks))
		return (NULL);
	cmds = cmd_new();
	cur = cmds;
	while (toks && cur)
	{
		if (toks->type == T_PIPE)
		{
			cur = new_pipe_segment(cur);
			toks = toks->next;
		}
		else if (toks->type == T_WORD)
			toks = add_arg(cur, toks);
		else
			toks = add_redir(cur, toks);
	}
	return (cmds);
}
