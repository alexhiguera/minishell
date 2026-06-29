/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	process_line(t_shell *sh, char *line)
{
	t_token	*toks;

	sh->line = line;
	sh->cmds = NULL;
	toks = NULL;
	if (has_content(line))
	{
		toks = lex(line);
		if (!toks)
		{
			cmd_error("syntax error", "unclosed quotes");
			sh->exit_status = 2;
		}
	}
	if (toks)
	{
		expand_tokens(sh, toks);
		sh->cmds = parse(toks);
		token_clear(&toks);
		if (sh->cmds)
			execute(sh, sh->cmds);
		else
			sh->exit_status = 2;
	}
	cleanup_after(sh);
}

void	shell_loop(t_shell *sh)
{
	char	*line;

	while (1)
	{
		setup_signals_interactive();
		line = readline(PROMPT);
		if (g_signal == SIGINT)
		{
			sh->exit_status = 130;
			g_signal = 0;
		}
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (*line)
			add_history(line);
		process_line(sh, line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	sh;

	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("minishell: no arguments expected", 2);
		return (1);
	}
	sh.env = env_init(envp);
	sh.cmds = NULL;
	sh.line = NULL;
	sh.exit_status = 0;
	shell_loop(&sh);
	env_clear(&sh.env);
	rl_clear_history();
	return (sh.exit_status);
}
