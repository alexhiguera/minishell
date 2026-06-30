/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static t_ast	*ast_new(t_ntype type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmds = NULL;
	node->left = NULL;
	node->right = NULL;
	node->redirs = NULL;
	return (node);
}

t_ast	*ast_pipeline(t_cmd *cmds)
{
	t_ast	*node;

	node = ast_new(N_PIPE);
	if (!node)
	{
		cmd_list_clear(cmds);
		return (NULL);
	}
	node->cmds = cmds;
	return (node);
}

t_ast	*ast_binary(t_ntype type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ast_new(type);
	if (!node)
	{
		ast_clear(left);
		ast_clear(right);
		return (NULL);
	}
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*ast_subshell(t_ast *child)
{
	t_ast	*node;

	node = ast_new(N_SUB);
	if (!node)
	{
		ast_clear(child);
		return (NULL);
	}
	node->left = child;
	return (node);
}

void	ast_clear(t_ast *node)
{
	if (!node)
		return ;
	ast_clear(node->left);
	ast_clear(node->right);
	if (node->cmds)
		cmd_list_clear(node->cmds);
	redir_clear(node->redirs);
	free(node);
}
