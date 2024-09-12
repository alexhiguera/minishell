/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:09:30 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 15:42:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_export(char *input, char **envp)
{
	char	*token;
	char	*name;
	char	*val;
	char	*input_cpy;
	char	*eq_sign;

	input_cpy = strdup(input);
	token = strtok(input_cpy, " ");
	while (token)
	{
		eq_sign = strchr(token, '=');
		if (eq_sign)
		{
			*eq_sign = '\0';
			name = token;
			val = eq_sign + 1;
			ft_add_update_env(name, val, envp);
		}
		token = strtok(NULL, " ");
	}
	free(input_cpy);
	return (1);
}

void	ft_add_update_env(char *name, char *value, char **envp)
{
	int		idx;
	int		idy;
	char	*new_var;

	idx = ft_find_env(name, envp);
	new_var = ft_create_env(name, value);
	if (idx != -1)
	{
		envp[idx] = new_var;
		envp[idx + 1] = NULL;
	}
	else
	{
		idy = 0;
		while (envp[idy] != NULL)
			idy++;
		envp[idy] = new_var;
		envp[idy + 1] = NULL;
	}
}

int	ft_find_env(char *name, char **envp)
{
	int	idx;

	idx = 0;
	while (envp[idx] != NULL)
	{
		if (ft_strncmp(envp[idx], name, strlen(name)) == 0)
			return (idx);
		idx++;
	}
	return (-1);
}

char	*ft_create_env(char *name, char *value)
{
	int		len;
	char	*new_var;

	len = strlen(name) + strlen(value) + 2;
	new_var = malloc(sizeof(char *) * len);
	strcpy(new_var, name);
	strcat(new_var, "=");
	strcat(new_var, value);
	return (new_var);
}
