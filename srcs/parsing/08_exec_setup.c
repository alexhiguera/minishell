/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_exec_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:08:05 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 12:08:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_clean_input_ex(char **input)
{
    char *str;
    char *end;
	
	str = *input;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';
    while (*str && isspace((unsigned char)*str))
        str++;
    if (str != *input)
        memmove(*input, str, strlen(str) + 1);
}

t_cmd *ft_create_cmd(char *cmd_str, int in_fd)
{
    t_cmd	*cmd = malloc(sizeof(t_cmd));
	char	**splitted_input;

	splitted_input = ft_split(cmd_str, ' ');
    cmd->cmd = strdup(cmd_str);
    cmd->path = ft_find_command_path(splitted_input[0]);
    cmd->args = ft_split(cmd_str, ' ');
    cmd->in_fd = in_fd;
    cmd->out_fd = 1;
    cmd->next = NULL;
	ft_free_spltinput(splitted_input);
    return (cmd);
}

t_cmd *ft_parse_cmds(char *input, int *flag)
{
    t_cmd	*cmd_list;
    t_cmd	*last_cmd;
    char 	**cmds;
	t_cmd	*new_cmd;
	int		idx;

	cmds = ft_split(input, '|');
	cmd_list = NULL;
	last_cmd = NULL;
	idx = 0;
    while (cmds[idx])
    {
        new_cmd = ft_create_cmd(cmds[idx], *flag);
        if (!cmd_list)
            cmd_list = new_cmd;
        else
            last_cmd->next = new_cmd;
        last_cmd = new_cmd;
		idx++;
		*flag = -1;
    }
    ft_free_spltinput(cmds);
    return (cmd_list);
}
