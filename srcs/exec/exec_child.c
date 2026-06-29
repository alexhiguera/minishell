/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_dup(t_cmd *cmd, int prev_fd, int *pipefd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
}

void	run_external(t_shell *sh, t_cmd *cmd)
{
	char	*path;
	char	**envp;
	int		code;

	path = NULL;
	code = resolve_path(sh, cmd->argv[0], &path);
	if (code)
		shell_exit(sh, code);
	envp = env_to_array(sh->env);
	execve(path, cmd->argv, envp);
	cmd_error(cmd->argv[0], strerror(errno));
	free(path);
	ft_free_array(envp);
	shell_exit(sh, 126);
}

void	child_process(t_shell *sh, t_cmd *cmd, int prev_fd, int *pipefd)
{
	setup_signals_default();
	child_dup(cmd, prev_fd, pipefd);
	if (apply_redirs(cmd) < 0)
		shell_exit(sh, 1);
	if (!cmd->argv[0])
		shell_exit(sh, 0);
	if (is_builtin(cmd->argv[0]))
		shell_exit(sh, run_builtin(sh, cmd->argv));
	run_external(sh, cmd);
}
