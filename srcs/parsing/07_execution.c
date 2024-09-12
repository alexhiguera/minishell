/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:07:38 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 12:07:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_execution(char *input, char **envp)
{
    t_cmd	*cmd_list; 
	int		flag;

	flag = 0;
	ft_clean_input_ex(&input);
	cmd_list = ft_parse_cmds(input, &flag);
    if (!cmd_list)
	    return ;
    ft_execute_cmds(cmd_list, envp);
    ft_free_cmd_list(cmd_list);
    return ;
}


void ft_execute_cmds(t_cmd *cmd_list, char **envp)
{
    t_cmd	*cmd;
	pid_t	pid;
    int		pipefd[2];

	cmd = cmd_list;
    while (cmd)
    {
        if (cmd->next)
            ft_create_pipe(pipefd);
        pid = ft_fork_and_execute(cmd, envp, pipefd);
        if (pid > 0)
            ft_parent_process(cmd, pipefd);
        cmd = cmd->next;
    }
}

pid_t ft_fork_and_execute(t_cmd *cmd, char **envp, int pipefd[2])
{
    pid_t pid;

	pid = fork();
    if (pid == 0)
    {
        if (cmd->in_fd != 0)
            dup2(cmd->in_fd, 0);
        if (cmd->next)
            dup2(pipefd[1], 1);
        ft_handle_redirection(cmd->cmd, &cmd->out_fd);
        ft_redirect_io(cmd->in_fd, cmd->out_fd);
        if (execve(cmd->path, cmd->args, envp) == -1)
        {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
    }
    return pid;
}

void ft_parent_process(t_cmd *cmd, int pipefd[2])
{
    if (cmd->next)
        close(pipefd[1]);
    if (cmd->in_fd != 0)
        close(cmd->in_fd);
    waitpid(-1, NULL, 0);
    if (cmd->next)
        cmd->next->in_fd = pipefd[0];
}

char *ft_find_command_path(char *cmd_name)
{
	char	*path_env;
    char	*path_cpy;
    char	*dir;
    char	full_path[1024];

	path_env = getenv("PATH");
	path_cpy = strdup(path_env);
	dir = strtok(path_cpy, ":");
    while (dir != NULL)
    {
		full_path[0] = '\0';
		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, cmd_name);
        if (access(full_path, X_OK) == 0)
        {
            free(path_cpy);
            return strdup(full_path);
        }
        dir = strtok(NULL, ":");
    }
    free(path_cpy);
    return NULL;
}
