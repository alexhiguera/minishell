/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	bi_env(t_shell *sh)
{
	t_env	*e;

	e = sh->env;
	while (e)
	{
		if (e->value)
		{
			ft_putstr_fd(e->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(e->value, 1);
		}
		e = e->next;
	}
	return (0);
}
