/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:33:23 by jvalenci          #+#    #+#             */
/*   Updated: 2022/07/08 18:59:13 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		counter++;
		s++;
	}
	return (counter);
}
