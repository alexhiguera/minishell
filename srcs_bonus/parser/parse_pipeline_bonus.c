/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	is_logic_end(t_tok type)
{
	return (type == T_AND || type == T_OR
		|| type == T_RPAREN || type == T_LPAREN);
}

static int	is_redir_tok(t_tok type)
{
	return (type == T_IN || type == T_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

void	collect_redirs(t_token **cur, t_redir **list)
{
	while (*cur && is_redir_tok((*cur)->type))
		*cur = add_redir_to(list, *cur);
}

t_ast	*parse_pipeline_node(t_token **cur)
{
	t_cmd	*cmds;
	t_cmd	*c;

	cmds = cmd_new();
	c = cmds;
	while (c && *cur && !is_logic_end((*cur)->type))
	{
		if ((*cur)->type == T_PIPE)
		{
			c->next = cmd_new();
			c = c->next;
			*cur = (*cur)->next;
		}
		else if ((*cur)->type == T_WORD)
			*cur = add_arg(c, *cur);
		else
			*cur = add_redir(c, *cur);
	}
	return (ast_pipeline(cmds));
}
