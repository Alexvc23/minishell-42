/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varTools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:13:11 by jvalenci          #+#    #+#             */
/*   Updated: 2022/07/08 11:49:36 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* cheks if we've got a string following the next contiditions "$?
if yes, it returns 1 otherwise returns 0 */
int	ft_check_is_var(char *result, int i)
{
	if (result[i] == '$' && ft_var_quotes(result, i, 1) == 0
		&& result[i + 1] && result[i + 1] != ' ')
		return (1);
	return (0);
}

/* 
Extract substring before variable if any
-> inicial string: "this is 42 school $var the best"
-> result: "this is 42 school "
*/
void	ft_set_start(char **result, int i, char **tempStart)
{
	if (i > 0)
		*tempStart = ft_substr(*result, 0, i);
}

/* 
Joins tempResult being the combination between substring before variable
and variable, with substring after variable
example join("this is 42 school $expanded", "the best")
result: "this is 42 school $expanded the best"
 */
void	ft_rest_while(char **tempEnd, int *i, char **result, char **tempResult)
{
	free(*result);
	*i = ft_strlen(*tempResult) - 1;
	*result = ft_own_strjoin(*tempResult, *tempEnd);
}

/* 
Substracs substring after variable if any, else return empty string
-> inicial string: "this is 42 school $var the best"
-> result: " the best"
*/
void	ft_set_temp_end(char **result, int i, char **tempEnd)
{
	*tempEnd = ft_substr(*result, ft_get_next_space(*result, i + 1) + 1,
			ft_strlen(*result) - (ft_get_next_space(*result, i + 1) + 1));
}

/* 
Joins substrings before variable and expanded variable if any 
example: join("this is 42 school", "$expanded")
result: "this is 42 school $expanded"
*/
void	ft_set_temp_result(char **result, char **tempStart, char **tempResult)
{
	*tempResult = ft_own_strjoin(*tempStart,
			ft_get_node_value(&g_vars->env, *result));
}
