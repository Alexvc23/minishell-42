/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:53:12 by jvalenci          #+#    #+#             */
/*   Updated: 2022/11/15 09:03:27 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*inicialize_heredoc(void)
{
	t_heredoc	*temp;

	temp = malloc(sizeof(t_heredoc));
	if (!temp)
		return (NULL);
	temp->path = NULL;
	temp->i = -1;
	temp->heredoc = NULL;
	temp->temp = NULL;
	temp->is_open = -1;
	temp->pid = 0;
	return (temp);
}

/** 
	@brief Do variable explantion if heredoc delimiter is not surrounded 
	in single quotes 
	1. if heredoc demiter is not quoted we search for variables in t_env
	structure and we expand it in current line
	2. else join current line with the previous one if any, storing it in final
	3. free unnecessary variables
	4. return final
**/
char	*ft_set_s(char *line, char *previous, int isInquote)
{
	char	*temp;
	char	*final;
	char	*temp2;

	temp2 = NULL;
	temp = NULL;
	final = NULL;
	if (isInquote == 0)
	{
		temp2 = ft_with_var(line, NULL, NULL, 0);
		temp = ft_strjoin(temp2, "\n");
	}
	else
		temp = ft_strjoin(line, "\n");
	if (previous)
		final = ft_strjoin(previous, temp);
	else
		final = ft_strdup(temp);
	free(temp);
	if (temp2)
		free(temp2);
	if (previous)
		free(previous);
	return (final);
}

/**
	@brief Looks for quotes in the heredoc delimiter, retourn 1 if any found
**/
int	ft_quote_in_heredoc(char *end)
{
	int	i;

	i = 0;
	while (end[i])
	{
		if (end[i] == '\'' || end[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

/** 
	@brief checks if heredoc delimiter exists. 
	2. checks if there are quotes 
**/
void	ft_bool_heredoc(char **end, int i, int *bool_quote, char **result)
{
	if (!end[i] && !*result)
		*result = ft_strdup("");
	if (end[i])
		*bool_quote = ft_quote_in_heredoc(end[i]);
	else
		*bool_quote = 0;
}

int	ft_open(int mode, char *path)
{
	int	is_open;

	if (mode == 2)
		is_open = open(path, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		is_open = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	return (is_open);
}