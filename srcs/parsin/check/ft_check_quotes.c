/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:03:02 by jvalenci          #+#    #+#             */
/*   Updated: 2022/06/14 11:46:28 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* Checks correct quote insertion, making sure ther each quote character has a 
   pair  */
void	ft_check_quotes(char *line)
{
	char	quote;
	int		i;

	i = -1;
	quote = 0;
	while (line[++i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '\"'))
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
	}
	if (quote)
		printf("%s\n", "Syntax error: wrong quotation usage");
	else
		ft_check_redir(line);
}
