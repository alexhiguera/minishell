/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: columbux <columbux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:11:35 by ahigura           #+#    #+#             */
/*   Updated: 2024/05/12 21:26:48 by columbux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	input[1024];

	while (true)
	{
		ft_printf("minishell/> ");
		if (fgets(input, sizeof(input), stdin) == NULL)
			exit(EXIT_FAILURE);
		add_history(input);
		ft_printf("%s", input);
	}
	return (0);
}
