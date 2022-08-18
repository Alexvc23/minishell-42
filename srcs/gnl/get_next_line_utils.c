/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:04:12 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/18 15:42:13 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strfelement(char *string, char c)
{
	char	*part;
	size_t	i;

	i = 0;
	while (string[i] != c && string[i])
		i++;
	if (string[i] == c)
		i++;
	part = malloc(sizeof(char) * i + 1);
	if (!part)
		return (0);
	i = 0;
	while (string[i] != c && string[i])
	{
		part[i] = string[i];
		i++;
	}
	if (string[i] == c)
	{
		part[i] = string[i];
		i++;
	}
	part[i] = '\0';
	return (part);
}

char	*ft_strchr_gnl(const char *str, char c)
{
	int	cur_str;

	cur_str = 0;
	while (str[cur_str] && str[cur_str] != c)
		cur_str++;
	if (str[cur_str] == c || c == '\0')
		return ((char *)&str[cur_str]);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*cast_dst;
	unsigned char	*cast_src;

	if (!dst && !src)
		return (0);
	i = 0;
	cast_dst = (unsigned char *) dst;
	cast_src = (unsigned char *) src;
	while (i < n)
	{
		cast_dst[i] = cast_src[i];
		i++;
	}
	return ((void *)cast_dst);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	i;
	char	*join;

	if (!s2)
		return (s1);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	i = 0;
	join = malloc((l1 + l2 + 1) * sizeof(char));
	if (!join)
		return (0);
	ft_memcpy(join, s1, l1);
	while (i < l2)
	{
		join[i + l1] = s2[i];
		i++;
	}
	join[l1 + l2] = '\0';
	free(s1);
	return (join);
}
