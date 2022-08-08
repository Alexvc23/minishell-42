/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:44:40 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/08 16:54:23 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
-> Analyze string backwards as this function will be used reading string 
character by character.
-> It will return 0 if there are not quotes or if single quotes where provided
correctly otherwise it will return 1
 */
int	ft_singlequotes(char *str, int index)
{
	int	i;
	int	bool_quote;

	i = index;
	bool_quote = 0;
	while (i >= 0)
	{
		if (str[i] == '\'' && bool_quote == 0 && !ft_doublequotes(str, index))
			bool_quote = 1;
		else if ((str[i] == '\'') && bool_quote == 1 && \
			!ft_doublequotes(str, index))
			bool_quote = 0;
		i--;
	}
	return (bool_quote);
}

/* 
-> Analyze string backwards as this function will be used reading string 
character by character.
-> It will return 0 if there are not quotes or if double quotes where provided
correctly, otherwise it will return 1
 */
int	ft_doublequotes(char *str, int index)
{
	int	i;
	int	bool_quote;

	i = index;
	bool_quote = 0;
	while (i >= 0)
	{
		if (str[i] == '"' && bool_quote == 0 && !ft_singlequotes(str, index))
			bool_quote = 1;
		else if ((str[i] == '"') && bool_quote == 1
			&& !ft_singlequotes(str, index))
		bool_quote = 0;
		i--;
	}
	return (bool_quote);
}

void	without_quote_thing(char **thing)
{
	char	*temp;

	temp = ft_strdup(*thing);
	free(*thing);
	*thing = ft_gro_quotes(temp);
	free(temp);
}

void	without_quote_args(t_cmd *env)
{
	int		i;

	i = 0;
	while (env->argv[i])
	{
		without_quote_thing(&env->argv[i]);
		i++;
	}
	if (env->out)
		without_quote_thing(&env->out);
	if (env->in)
		without_quote_thing(&env->in);
}

/* 
-> checks if a word (variable or cmd) is surrounded by quotes 
-> Additinally, checks if a variable ($) is preceded by (") doublequotes
 */
int	ft_var_quotes(char *var, int index, int dollar)
{
	if (ft_singlequotes(var, index))
		return (1);
	else if (ft_doublequotes(var, index))
	{
		if (dollar && var[index] == '$')
			return (0);
		return (1);
	}
	return (0);
}
