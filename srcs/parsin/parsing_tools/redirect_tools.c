/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:22:37 by jvalenci          #+#    #+#             */
/*   Updated: 2022/07/08 12:10:53 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
take heredoc delimeter string and stores it in a 2 dimentional
array
*/
char **ft_alloc_delimiter(char **result, char *value)
{
    char **final;
    int i;

    i = 0;
    final = (char **)malloc(sizeof(char *) * 2);
    if (!final)
        return (NULL);
    final[i] = value;
    final[i + 1] = NULL;
    if (result)
        ft_free((void **)result);
    return (final);
}

/* 
-> checks if redirection metacharacter has no space between file name,
if no space between, joins a space at the end
-> return the fist indext of the last word in the string 
*/
void	ft_get_index_last(char *new, int *i, char **temp, char **start)
{
	if (new[*i + 1] && (new[*i + 1] == '>' || new[*i + 1] == '<'))
		(*i)++;
	if (new[*i + 1] && new[*i + 1] != ' ')
	{
		*temp = ft_strjoin(*start, " ");
		free(*start);
		*start = *temp;
	}
	while (new[*i] && (new[*i] == '>' || new[*i] == '<' || new[*i] == ' '))
		(*i)++;
	while (new[*i] && (new[*i] != ' ' || ft_var_quotes(new, *i, 0) == 1))
		(*i)++;
	while (new[*i] && new[*i] == ' ')
		(*i)++;
}

/* 
Get rid of any redirection metacharacter and any word to its right
in order to filter cmds and arguments 
*/
char	*ft_conv_redir(char *cmd)
{
	int		i;
	char	*new;
	char	*start;
	char	*end;
	char	*temp;

	i = 0;
	new = ft_strdup(cmd);
	while (new[i])
	{
		if ((new[i] == '>' || new[i] == '<') && ft_var_quotes(cmd, i, 0) == 0)
		{
			start = ft_substr(new, 0, i);
			ft_get_index_last(new, &i, &temp, &start);
			end = ft_substr(new, i, ft_strlen(new + i));
			free(new);
			new = ft_strjoin(start, end);
			free(start);
			free(end);
			i = 0;
		}
		i++;
	}
	return (new);
}

/* 
fetch the word that is besides the metacharacter '<', calculating
the size and the index where it should extrac the word, then pass it 
as argument to the fuction ft_substr, returning the word we are looking
for
*/
char  *ft_get_afterre(char *cmd, int index, int heredoc)
{
    int i;
    int start;

    start = index + 1 + heredoc;
    if (!cmd[start] == 0)
        return (NULL);
    while (cmd[start] == ' ')
        start++;
    i = start;
    while ((cmd[i] != ' ' || ft_var_quotes(cmd, i, 0) == 1) &&
            cmd[i] != '\0')
            i++;
    return (ft_substr(cmd, start, i - start));
}

/* 
if next character is '>' set mode = 2 and extract file name into path
*/
void	ft_cut_re(int *mode, char **path, int *i, char *cmd)
{
	free(*path);
	*path = NULL;
	if (cmd[*i + 1] && cmd[*i + 1] == '>')
	{
		*mode = 2;
		*path = ft_get_afterre(cmd, *i + 1, 0);
		(*i)++;
	}
	else
	{
		*mode = 1;
		*path = ft_get_afterre(cmd, *i, 0);
	}
}

