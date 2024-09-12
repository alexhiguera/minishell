/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:04:49 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 12:33:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc(char **pre_input)
{
	int		s_quotes;
	int		d_quotes;
	char	*temp;
	char	*hd_input;

	s_quotes = ft_count_q(*pre_input, 0);
	d_quotes = ft_count_q(*pre_input, 1);
	while (s_quotes % 2 != 0 || d_quotes % 2 != 0)
	{
		hd_input = readline("quote> ");
		if (!hd_input)
			return ;
		temp = ft_append_input(*pre_input, hd_input);
		if (temp == NULL)
			return ;
		*pre_input = temp;
		free(hd_input);
		s_quotes = ft_count_q(*pre_input, 0);
		d_quotes = ft_count_q(*pre_input, 1);
	}
}

int	ft_count_q(char *input, int x)
{
	int	idx;
	int	count;

	count = 0;
	idx = 0;
	while (input[idx] && x == 0)
	{
		if (input[idx] == '\'')
			count++;
		idx++;
	}
	while (input[idx] && x == 1)
	{
		if (input[idx] == '"')
			count++;
		idx++;
	}
	return (count);
}

char	*ft_append_input(char *pre_input, char *hd_input)
{
	char	*new_input;
	int		len_pre;
	int		len_hd;

	len_pre = strlen(pre_input);
	len_hd = strlen(hd_input);
	new_input = realloc(pre_input, len_pre + len_hd + 1);
	strcat(new_input, hd_input);
	return (new_input);
}
