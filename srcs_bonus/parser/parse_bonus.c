/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static t_ast	*parse_subshell(t_token **cur)
{
	t_ast	*child;
	t_ast	*sub;

	*cur = (*cur)->next;
	child = parse_and_or(cur);
	if (!child)
		return (NULL);
	if (!*cur || (*cur)->type != T_RPAREN)
	{
		ast_clear(child);
		return (NULL);
	}
	*cur = (*cur)->next;
	sub = ast_subshell(child);
	if (sub)
		collect_redirs(cur, &sub->redirs);
	return (sub);
}

static t_ast	*parse_primary(t_token **cur)
{
	if (*cur && (*cur)->type == T_LPAREN)
		return (parse_subshell(cur));
	return (parse_pipeline_node(cur));
}

t_ast	*parse_and_or(t_token **cur)
{
	t_ast	*node;
	t_ast	*right;
	t_ntype	op;

	node = parse_primary(cur);
	while (node && *cur && ((*cur)->type == T_AND || (*cur)->type == T_OR))
	{
		op = N_OR;
		if ((*cur)->type == T_AND)
			op = N_AND;
		*cur = (*cur)->next;
		right = parse_primary(cur);
		if (!right)
		{
			ast_clear(node);
			return (NULL);
		}
		node = ast_binary(op, node, right);
	}
	return (node);
}

t_ast	*parse(t_token *toks)
{
	t_token	*cur;
	t_ast	*ast;

	if (!syntax_check(toks))
		return (NULL);
	cur = toks;
	ast = parse_and_or(&cur);
	if (ast && cur)
	{
		ast_clear(ast);
		return (NULL);
	}
	return (ast);
}
