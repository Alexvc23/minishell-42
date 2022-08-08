/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:55:56 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/08 16:55:59 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* 
Search for white spaces at the beginning of string
return number of characters skiped 
*/
int	ft_white_spaces(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i == 0)
		return (1);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
	{
		str++;
		i--;
	}
	return (i);
}

/* 
fetch fist word before space
*/
char	*ft_get_first(char *cmd_b)
{
	int	i;

	i = 0;
	while (cmd_b[i] && (cmd_b[i] != ' ' || ft_var_quotes(cmd_b, i, 0) == 1) && \
		cmd_b[i] != '\n')
		i++;
	return (ft_substr(cmd_b, 0, i));
}

/* 
Get rid of spaces at the begining of string
*/
char	*ft_skip_spaces(char *cmd_b)
{
	int		i;
	char	*res;

	i = 0;
	if (ft_white_spaces(cmd_b) == 0)
		return (cmd_b);
	while (cmd_b[i] && cmd_b[i] == ' ')
		i++;
	res = ft_substr(cmd_b, i, ft_strlen(cmd_b) - i);
	free(cmd_b);
	return (res);
}

/* 
-> allocate memory in cmd->argv and set 1 as error in argv[0][0] 
-> free cmd->in and cmd->out if anything 
*/
void	ft_fill_err(t_cmd *cmd)
{
	cmd->argv = malloc(2 * sizeof(char *));
	cmd->argv[0] = malloc(2);
	cmd->argv[1] = NULL;
	cmd->argv[0][0] = 1;
	cmd->argv[0][1] = 0;
	cmd->heredoc = 0;
	if (cmd->in)
		free(cmd->in);
	cmd->in = NULL;
	if (cmd->out)
		free(cmd->out);
	cmd->out = NULL;
	cmd->next = NULL;
}

/* 
free temp strings in ft_fill_cmd function
*/
void	ft_free_multiple(char *one, char *two, char *tree, char *four)
{
	if (one)
		free(one);
	if (two)
		free(two);
	if (tree)
		free(tree);
	if (four)
		free(four);
}
