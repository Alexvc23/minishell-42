/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:19:05 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/17 18:19:42 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Compare the two strings to know if they are equal or not

int	ft_strequ(char *s1, char *s2)
{
	size_t	i;
	size_t	len;

	if (!s1 || !s2 || ft_strlen(s1) != ft_strlen(s2))
		return (0);
	i = -1;
	len = ft_strlen(s1);
	while (++i < len)
		if (s1[i] != s2[i])
			return (0);
	return (1);
}
