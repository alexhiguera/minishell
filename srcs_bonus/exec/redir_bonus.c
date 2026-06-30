/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	open_redir(t_redir *r)
{
	int	fd;

	if (r->type == R_HEREDOC)
		return (r->fd);
	if (r->type == R_IN)
		fd = open(r->target, O_RDONLY);
	else if (r->type == R_APPEND)
		fd = open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		cmd_error(r->target, strerror(errno));
	return (fd);
}

int	apply_redirs(t_redir *redirs)
{
	t_redir	*r;
	int		fd;

	r = redirs;
	while (r)
	{
		fd = open_redir(r);
		if (fd < 0)
			return (-1);
		if (r->type == R_IN || r->type == R_HEREDOC)
			dup2(fd, 0);
		else
			dup2(fd, 1);
		close(fd);
		if (r->type == R_HEREDOC)
			r->fd = -1;
		r = r->next;
	}
	return (0);
}
