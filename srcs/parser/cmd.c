/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(char *));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	cmd->argv[0] = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

char	**argv_add(char **argv, char *str)
{
	int		n;
	int		i;
	char	**new;

	n = 0;
	while (argv && argv[n])
		n++;
	new = malloc(sizeof(char *) * (n + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new[i] = argv[i];
		i++;
	}
	new[n] = str;
	new[n + 1] = NULL;
	free(argv);
	return (new);
}

t_token	*add_arg(t_cmd *cmd, t_token *tok)
{
	char	**new;

	if (tok->value[0] == '\0' && !tok->quoted)
		return (tok->next);
	new = argv_add(cmd->argv, ft_strdup(tok->value));
	if (new)
		cmd->argv = new;
	return (tok->next);
}

void	cmd_clear(t_cmd *cmd)
{
	if (cmd->argv)
		ft_free_array(cmd->argv);
	redir_clear(cmd->redirs);
	free(cmd);
}

void	cmd_list_clear(t_cmd *cmds)
{
	t_cmd	*next;

	while (cmds)
	{
		next = cmds->next;
		cmd_clear(cmds);
		cmds = next;
	}
}
