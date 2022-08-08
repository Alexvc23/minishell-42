/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:45:52 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/08 16:07:34 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Get rid of the first single or double quoutes match, 
as long as we are not mixing them up in
same string, returns a new string without quotes if we respect the
conditions stablished */
char	*ft_gro_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if ((str[i] == '\'' && !ft_doublequotes(str, i))
			|| (str[i] == '"' && !ft_singlequotes(str, i)))
		{
			i++;
			continue ;
		}
		result[j] = str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}
