/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:09:18 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 14:53:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd(char *input)
{
	int		len;
	char	*dir;

	len = 0;
	dir = NULL;
	while (input[len])
		len++;
	if (len == 2)
	{
		dir = getenv("HOME");
		chdir(dir);
	}
	else if (len == 4 && ft_strncmp(input, "cd -", 4) == 0)
	{
		dir = getenv("OLDPWD");
		chdir(dir);
	}
	else
		return (ft_cd2(input, len));
	return (1);
}

int	ft_cd2(char *input, int len)
{
	char	*abs_path;
	char	**splt_input;

	abs_path = NULL;
	splt_input = NULL;
	if (len > 5)
	{
		splt_input = ft_split(input, ' ');
		abs_path = splt_input[1];
		if (chdir(abs_path) != 0)
		{
			printf("No se puede cambiar a la ruta especificada.\n");
			ft_free_spltinput(splt_input);
			return (1);
		}
		ft_free_spltinput(splt_input);
		return (1);	
	}
	else if (len == 5 && ft_strncmp(input, "cd ..", 5) == 0)
		chdir("..");
	return (1);
}
