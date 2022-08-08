/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:38:25 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/08 17:25:44 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
-> if heredoc demiter is not quoted we search for variables in t_env
structure and we expand it in current line
-> else join current line with the previous one if any, storing it in final
-> free unnecessary variables
-> return final
*/
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

/* vefify is there are any quote in the heredoc delimiter */
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

/* 
cheks if heredoc delimiter exists. With the help of check_heredoc_quote
determines if there are quotes in delimiter if so, store in bool_quote 
variable a boolean (1 or 0)
*/
void	ft_bool_heredoc(char **end, int i, int *bool_quote, char **result)
{
	if (!end[i] && !*result)
		*result = ft_strdup("");
	if (end[i])
		*bool_quote = ft_quote_in_heredoc(end[i]);
	else
		*bool_quote = 0;
}

/* 
-> we read from std input storinig it in a string using readline Function
-> checks if **delimiter is sourrended by quotes
-> As long as we haven't reached NULL in **delimiter variable, we check if
we have to do a variable substitution with the help of function ft_set_s
-> we free line variable beause we have now a new string called final_line
being the result of the previous step and function ft_set_s
-> we free temp being the result of end[i](**delimiter) without quotes
we won't use it any more
-> we free **end as we won't use it anymore, we have already determined a
file descriptor
-> Modify structure t_cmd, setting element struc->heredoc = 1, so 
the execution part will know what to do
-> we return the final_string contaning checked information to set it
as input in t_cmd structure
*/
char	*ft_heredoc(char **end, t_cmd *stru, char *final_line)
{
	int		i;
	int		bool_quote;
	char	*line;
	char	*temp;

	i = 0;
	while (end[i])
	{
		line = readline("\033[31mHEREDOC\033[0m> ");
		if (!line)
			break ;
		temp = ft_gro_quotes(end[i]);
		if (ft_strcmp2(line, temp))
			i++;
		ft_bool_heredoc(end, i, &bool_quote, &final_line);
		if (end[i])
			final_line = ft_set_s(line, final_line, bool_quote);
		free(line);
		free(temp);
	}
	ft_free((void **)end);
	stru->heredoc = 1;
	return (final_line);
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
