/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_new(char *value, t_tok type)
{
	t_token	*tok;

	if (!value)
		return (NULL);
	tok = malloc(sizeof(t_token));
	if (!tok)
	{
		free(value);
		return (NULL);
	}
	tok->value = value;
	tok->type = type;
	tok->quoted = 0;
	tok->next = NULL;
	return (tok);
}

void	token_add_back(t_token **lst, t_token *node)
{
	t_token	*last;

	if (!node)
		return ;
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

void	token_clear(t_token **lst)
{
	t_token	*cur;
	t_token	*next;

	cur = *lst;
	while (cur)
	{
		next = cur->next;
		free(cur->value);
		free(cur);
		cur = next;
	}
	*lst = NULL;
}
