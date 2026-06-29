/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_id(char *arg, char *eq)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while ((eq && arg + i < eq) || (!eq && arg[i]))
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_one(t_shell *sh, char *arg)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (!is_valid_id(arg, eq))
	{
		cmd_error2("export", arg, "not a valid identifier");
		return (1);
	}
	if (!eq)
	{
		env_declare(&sh->env, arg);
		return (0);
	}
	key = ft_substr(arg, 0, eq - arg);
	env_set(&sh->env, key, eq + 1);
	free(key);
	return (0);
}

int	bi_export(t_shell *sh, char **argv)
{
	int	i;
	int	ret;

	if (!argv[1])
		return (export_print(sh->env));
	i = 1;
	ret = 0;
	while (argv[i])
	{
		if (export_one(sh, argv[i]) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
