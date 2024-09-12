/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:08:58 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 12:39:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char *input)
{
	int	idx;
	int	flag;
	int	idk;

	flag = 1;
	idx = 0;
	idk = 0;
	while (input[idx])
	{
		if (input[idx] == '-' && input[idx + 1] == 'n')
			flag = 0;
		idx++;
	}
	if (flag == 0)
		idx = 7;
	else
		idx = 4;
	while (input[idx + 1] != '\0')
		idk = write(1, &input[++idx], 1);
	if (flag == 1 && idk)
		printf("\n");
	return (1);
}
