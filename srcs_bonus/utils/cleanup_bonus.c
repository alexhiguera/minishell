/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	free_shell(t_shell *sh)
{
	if (sh->ast)
		ast_clear(sh->ast);
	sh->ast = NULL;
	env_clear(&sh->env);
	free(sh->line);
	sh->line = NULL;
	rl_clear_history();
}

void	shell_exit(t_shell *sh, int code)
{
	free_shell(sh);
	exit(code);
}
