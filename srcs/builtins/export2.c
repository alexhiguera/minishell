/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	env_len(t_env *e)
{
	int	n;

	n = 0;
	while (e)
	{
		n++;
		e = e->next;
	}
	return (n);
}

static t_env	**collect_env(t_env *env, int n)
{
	t_env	**arr;
	int		i;

	arr = malloc(sizeof(t_env *) * (n + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	sort_env(t_env **arr, int n)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strncmp(arr[j]->key, arr[j + 1]->key,
					ft_strlen(arr[j]->key) + 1) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_one(t_env *e)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(e->key, 1);
	if (e->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(e->value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

int	export_print(t_env *env)
{
	t_env	**arr;
	int		n;
	int		i;

	n = env_len(env);
	arr = collect_env(env, n);
	if (!arr)
		return (1);
	sort_env(arr, n);
	i = 0;
	while (i < n)
		print_one(arr[i++]);
	free(arr);
	return (0);
}
