/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	env_count(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (env->value)
			n++;
		env = env->next;
	}
	return (n);
}

static char	*env_pair(t_env *e)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(e->key, "=");
	res = ft_strjoin(tmp, e->value);
	free(tmp);
	return (res);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (env_count(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
			arr[i++] = env_pair(env);
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	env_clear(t_env **env)
{
	t_env	*cur;
	t_env	*next;

	cur = *env;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	*env = NULL;
}
