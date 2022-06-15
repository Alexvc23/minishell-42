/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charnct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:18:56 by jvalenci          #+#    #+#             */
/*   Updated: 2022/06/15 10:44:22 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_charcnt(char *str, char c)
{
	int	counter;

	counter = 0;
	if (!str || !c)
		return (counter);
	while (*str && *str == c)
	{
		counter++;
		str++;
	}
	return (counter);
}
