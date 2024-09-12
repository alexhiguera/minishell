/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:07:15 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 12:07:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_checker(t_checker *checker)
{
	while (checker)
	{
		printf("data -> %s\n", checker->data);
		printf("datatype -> %i\n", checker->data_type);
		printf("pos -> %i\n", checker->pos);
		printf("-----------------------\n");
		checker = checker->next;
	}
}

void	ft_free_checker(t_checker *checker)
{
	t_checker *temp;

	while (checker != NULL)
	{
		temp = checker;
		checker = checker->next;
		ft_free_node(temp);
	}
}

void	ft_free_node(t_checker *node)
{
	if (node)
	{
		free(node->data);
		free(node);
	}
}
