/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:20:59 by marvin            #+#    #+#             */
/*   Updated: 2024/09/02 20:20:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*pre_input;
	char	*clean_input;

	pre_input = NULL;
	clean_input = NULL;
	ft_signal_handler();
	if (argc == 2 || argv[1])
		return (0);
	while (1)
	{
		pre_input = readline("minichel-> ");
		if (!pre_input)
			break ;
		ft_heredoc(&pre_input);
		add_history(pre_input);
		clean_input = ft_clean_input(pre_input);
		if (ft_builtin(clean_input, envp) == 0)
			ft_init_minishell(clean_input, envp);
		free(clean_input);
		free(pre_input);
	}
	return (0);
}
