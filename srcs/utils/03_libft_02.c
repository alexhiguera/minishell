/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_libft_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:12:57 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 12:13:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strtok(char *str, const char *delim)
{
    static char *lasts;
    char 		*start;

    if (str == NULL) {
        str = lasts;
    }
    str += strspn(str, delim);
    if (*str == '\0')
        return NULL;
    start = str;
    str = strpbrk(str, delim);
    if (str != NULL)
	{
        *str = '\0';
        lasts = str + 1;
	}
    else
        lasts = start + strlen(start);
    return start;
}

char *ft_strcat(char *dest, const char *src)
{
    char *ptr;

	ptr = dest;
    while (*ptr != '\0')
        ptr++;
    while (*src != '\0')
	{
        *ptr = *src;
        ptr++;
        src++;
    }
    *ptr = '\0';
    return dest;
}
