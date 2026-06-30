/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	exec_subshell(t_shell *sh, t_ast *node)
{
	pid_t	pid;
	int		status;

	setup_signals_exec();
	pid = fork();
	if (pid == 0)
	{
		setup_signals_default();
		if (apply_redirs(node->redirs) < 0)
			shell_exit(sh, 1);
		shell_exit(sh, eval_ast(sh, node->left));
	}
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	sh->exit_status = exit_code_of(status);
	return (sh->exit_status);
}

int	eval_ast(t_shell *sh, t_ast *node)
{
	if (!node)
		return (sh->exit_status);
	if (node->type == N_PIPE)
	{
		execute(sh, node->cmds);
		return (sh->exit_status);
	}
	if (node->type == N_SUB)
		return (exec_subshell(sh, node));
	if (node->type == N_AND)
	{
		if (eval_ast(sh, node->left) == 0)
			return (eval_ast(sh, node->right));
		return (sh->exit_status);
	}
	if (eval_ast(sh, node->left) != 0)
		return (eval_ast(sh, node->right));
	return (sh->exit_status);
}
