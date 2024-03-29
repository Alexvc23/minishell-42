/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 21:18:57 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/07 16:59:23 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* we compare two strings only if they have the same length, returning 1 (true) 
   or 0 (false) */
int	ft_strcmp2(char *s, char *s1)
{
	if (!s || !s1)
		return (0);
	if (ft_strlen(s) == ft_strlen(s1))
	{
		if (!ft_strncmp(s, s1, ft_strlen(s)))
			return (0);
	}
	return (1);
}
