/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_find(t_env *env, char *key)
{
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strlen(env->key) == len
			&& ft_strncmp(env->key, key, len) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*env_get(t_env *env, char *key)
{
	t_env	*node;

	node = env_find(env, key);
	if (node)
		return (node->value);
	return (NULL);
}
