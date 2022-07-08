/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:35:30 by jvalenci          #+#    #+#             */
/*   Updated: 2022/07/08 12:09:15 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks the following aspects
   - prints error if Token '|' is outside quotation marks in the case we are
   using them in the passed line
   - Prints error if token '|' is followed by '< >|' and not by any other 
   character alphanumeric character */

void	ft_manipulate(char *line, int err)
{
	t_cmd	*cmd;

	if (!err)
	{
		cmd = ft_parse_cmd(line);
		free(line);
		while (cmd)
		{
			printf("%s\n", cmd->argv[0]);
			cmd = cmd->next;
		}
	}
	else if (err == 1)
		printf("%s\n", "Syntax error: unexpected token ||");
	else if (err == 2)
		printf("%s\n", "Syntax error: unexpected token near '|'");
}

/* return 1 if we find an alphanumeric character before the token '|' else
   return 0, this function works along side ft_workfoce*/
int	ft_before_token(char *line, int i)
{
	int	j;

	j = 1;
	while (line[i - j])
	{
		if (ft_isalnum((int)line[i - j]))
			return (1);
		j++;
	}
	return (0);
}

/* this fonction works along side ft_check_pipe, checks if we are using only one '|'
metacharacter as we won't do the bunus part. Finally, it makes sure we are passing
an alphannumeric character after metacharacter pipe '|' */
void	ft_workforce(char *line, int i, int *err)
{
	int	j;
	int	found;

	j = 1;
	found = 0;
	if (line[i] == '|')
	{
		if (ft_charcnt(&line[i], '|') > 1)
			*err = 1;
		while (line[i + j])
		{
			if (!ft_strchr("< >|", line[i + j]))
				found = 1;
			j++;
		}
		if ((!*err && !found) || !ft_before_token(line, i))
			*err = 2;
	}
}

void	ft_check_pipe(char *line)
{
	char	quote;
	int		err;
	int		i;

	quote = 0;
	err = 0;
	i = -1;
	while (line[++i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '\"'))
			quote = line[i];
		else if (quote == line[i])
			quote = 0;
		if (quote)
			continue ;
		else
			ft_workforce(line, i, &err);
	}
	ft_manipulate(line, err);
}
