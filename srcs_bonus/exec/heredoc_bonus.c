/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	hd_is_delim(char *line, char *delim)
{
	if (ft_strlen(line) != ft_strlen(delim))
		return (0);
	return (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0);
}

static void	heredoc_loop(t_shell *sh, int wfd, t_redir *r)
{
	char	*line;
	char	*out;

	line = readline("> ");
	while (line)
	{
		if (hd_is_delim(line, r->target))
		{
			free(line);
			return ;
		}
		if (r->expand)
			out = expand_vars(sh, line);
		else
			out = ft_strdup(line);
		ft_putendl_fd(out, wfd);
		free(out);
		free(line);
		line = readline("> ");
	}
}

static void	heredoc_child(t_shell *sh, int *fd, t_redir *r)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	heredoc_loop(sh, fd[1], r);
	close(fd[1]);
	shell_exit(sh, 0);
}

static int	read_heredoc(t_shell *sh, t_redir *r)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
		heredoc_child(sh, fd, r);
	close(fd[1]);
	setup_signals_exec();
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status)))
	{
		close(fd[0]);
		sh->exit_status = 130;
		return (-1);
	}
	r->fd = fd[0];
	return (0);
}

int	heredocs_setup(t_shell *sh, t_cmd *cmds)
{
	t_redir	*r;

	while (cmds)
	{
		r = cmds->redirs;
		while (r)
		{
			if (r->type == R_HEREDOC && read_heredoc(sh, r) < 0)
				return (-1);
			r = r->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
