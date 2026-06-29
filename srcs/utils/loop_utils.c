/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_content(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && (line[i] < 9 || line[i] > 13))
			return (1);
		i++;
	}
	return (0);
}

void	cleanup_after(t_shell *sh)
{
	if (sh->cmds)
		cmd_list_clear(sh->cmds);
	sh->cmds = NULL;
	free(sh->line);
	sh->line = NULL;
}
