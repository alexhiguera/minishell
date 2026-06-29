/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **lst, t_env *node)
{
	t_env	*last;

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

static t_env	*pair_to_node(char *str)
{
	t_env	*node;
	char	*eq;

	eq = ft_strchr(str, '=');
	if (!eq)
		return (env_new(str, NULL));
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_substr(str, 0, eq - str);
	node->value = ft_strdup(eq + 1);
	node->next = NULL;
	return (node);
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		env_add_back(&env, pair_to_node(envp[i]));
		i++;
	}
	return (env);
}
