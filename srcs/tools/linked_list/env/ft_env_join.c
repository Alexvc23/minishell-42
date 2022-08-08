/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:20:18 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/08 13:28:49 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
Joins strings with character in the middle "="
*/
char	*ft_env_join(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}
