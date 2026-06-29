/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_set(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = env_find(*env, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
		return ;
	}
	env_add_back(env, env_new(key, value));
}

void	env_declare(t_env **env, char *key)
{
	if (env_find(*env, key))
		return ;
	env_add_back(env, env_new(key, NULL));
}

void	env_unset(t_env **env, char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (ft_strlen(cur->key) == ft_strlen(key)
			&& ft_strncmp(cur->key, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
