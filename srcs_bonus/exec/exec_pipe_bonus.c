/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	exit_code_of(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		else if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (WEXITSTATUS(status));
}

static void	wait_all(t_shell *sh, pid_t last)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last)
			sh->exit_status = exit_code_of(status);
		pid = wait(&status);
	}
}

static pid_t	launch(t_shell *sh, t_cmd *cmd, int *prev_fd)
{
	int		pipefd[2];
	pid_t	pid;

	pipefd[0] = -1;
	pipefd[1] = -1;
	if (cmd->next && pipe(pipefd) < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
		child_process(sh, cmd, *prev_fd, pipefd);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	return (pid);
}

void	exec_pipeline(t_shell *sh, t_cmd *cmds)
{
	int		prev_fd;
	pid_t	last;

	prev_fd = -1;
	last = -1;
	setup_signals_exec();
	while (cmds)
	{
		last = launch(sh, cmds, &prev_fd);
		cmds = cmds->next;
	}
	wait_all(sh, last);
	setup_signals_interactive();
}
