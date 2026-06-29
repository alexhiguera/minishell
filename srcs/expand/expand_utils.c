/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_val(char **dst, char *new)
{
	if (!new)
		return ;
	free(*dst);
	*dst = new;
}

char	*strip_quotes(char *raw)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(raw) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (raw[i])
	{
		if (raw[i] != '\'' && raw[i] != '"')
			res[j++] = raw[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
