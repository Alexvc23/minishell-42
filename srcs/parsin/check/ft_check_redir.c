/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 10:57:51 by jvalenci          #+#    #+#             */
/*   Updated: 2022/07/03 12:07:15 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_sub_redir(char *line, int *err, int i)
{
	int	j;
	int	found;

	i = 0;
	found = 0;
	j = (ft_charcnt(line, '<') + ft_charcnt(line, '>'));
	if (ft_charcnt(line, '<') > 2 || ft_charcnt(line, '>') > 2)
		*err = 1;
	else
	{
		while (line[i + j])
		{
			if (!ft_strchr("< >|", line[i + j]))
				found = 1;
			j++;
		}
	}
	if (!found && !*err)
		*err = 2;
}

/*	- checks there are no more that 3 '<' '>' metacaracters per token
	- checks there is at least one alphanumeric character after any of tokens
	- We are not verifying if we have a argument before token '< > << >> '
	as the error will be handled by the execution
	 "> < >> <<" */
void	ft_check_redir(char *line)
{
	int	i;
	int	err;

	i = -1;
	err = 0;
	while (line[++i])
	{
		if (line[i] == '<' || line[i] == '>')
			ft_sub_redir(&line[i], &err, i);
	}
	if (err == 1)
		printf("%s\n", "Minishell: syntax error unexpected \
				redirection operator");
	else if (err == 2)
		printf("%s\n", "Minishell: syntax error");
	else
		ft_check_pipe(line);
}
