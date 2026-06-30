/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	*gc_strjoin(char *s, char *add)
{
	char	*res;

	if (!s)
		return (NULL);
	res = ft_strjoin(s, add);
	free(s);
	return (res);
}

char	*str_append_n(char *s, char *add, int n)
{
	char	*sub;
	char	*res;

	if (!s)
		return (NULL);
	sub = ft_substr(add, 0, n);
	res = ft_strjoin(s, sub);
	free(sub);
	free(s);
	return (res);
}

char	*app_char(char *s, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (gc_strjoin(s, buf));
}
