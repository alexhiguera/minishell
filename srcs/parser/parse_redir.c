/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_redir_type	redir_type(t_tok type)
{
	if (type == T_IN)
		return (R_IN);
	if (type == T_OUT)
		return (R_OUT);
	if (type == T_APPEND)
		return (R_APPEND);
	return (R_HEREDOC);
}

static void	redir_add_back(t_redir **lst, t_redir *node)
{
	t_redir	*last;

	if (!*lst)
	{
		*lst = node;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = node;
}

t_token	*add_redir(t_cmd *cmd, t_token *tok)
{
	t_redir	*redir;
	t_token	*target;

	target = tok->next;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (target->next);
	redir->type = redir_type(tok->type);
	redir->target = ft_strdup(target->value);
	redir->expand = !(redir->type == R_HEREDOC && target->quoted);
	redir->fd = -1;
	redir->next = NULL;
	redir_add_back(&cmd->redirs, redir);
	return (target->next);
}

void	redir_clear(t_redir *r)
{
	t_redir	*next;

	while (r)
	{
		next = r->next;
		if (r->type == R_HEREDOC && r->fd > 2)
			close(r->fd);
		free(r->target);
		free(r);
		r = next;
	}
}
