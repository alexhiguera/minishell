/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_single(t_shell *sh, t_cmd *cmd)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(0);
	saved_out = dup(1);
	if (apply_redirs(cmd) < 0)
		ret = 1;
	else if (cmd->argv[0])
		ret = run_builtin(sh, cmd->argv);
	else
		ret = 0;
	dup2(saved_in, 0);
	dup2(saved_out, 1);
	close(saved_in);
	close(saved_out);
	sh->exit_status = ret;
}

void	execute(t_shell *sh, t_cmd *cmds)
{
	if (heredocs_setup(sh, cmds) < 0)
		return ;
	if (!cmds->next && (!cmds->argv[0] || is_builtin(cmds->argv[0])))
		exec_single(sh, cmds);
	else
		exec_pipeline(sh, cmds);
}
