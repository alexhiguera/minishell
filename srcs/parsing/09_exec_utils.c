/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:08:26 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 12:08:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_create_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1)
    {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
}

void ft_redirect_io(int in_fd, int out_fd)
{
    if (in_fd != 0)
        dup2(in_fd, 0);
    if (out_fd != 1)
        dup2(out_fd, 1);
    if (in_fd != 0)
        close(in_fd);
    if (out_fd != 1)
        close(out_fd);
}

void ft_handle_redirection(char *cmd, int *out_fd)
{
    char *redir = strchr(cmd, '>');
    if (redir != NULL)
    {
        *redir = '\0';
        redir++;
        while (*redir == ' ')
            redir++;

        int fd = open(redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("open failed");
            exit(EXIT_FAILURE);
        }
        *out_fd = fd;
    }
}

void ft_free_cmd(t_cmd *cmd)
{
	char	**arg;

	arg = cmd->args;
    if (cmd)
    {
        free(cmd->cmd);
        free(cmd->path);
        if (cmd->args)
        {
            while (*arg)
			{
				free(*arg);
				arg++;
			}
            free(cmd->args);
        }
        free(cmd);
    }
}

void ft_free_cmd_list(t_cmd *cmd_list)
{
    t_cmd *temp;

    while (cmd_list)
    {
        temp = cmd_list;
        cmd_list = cmd_list->next;
        ft_free_cmd(temp);
    }
}
