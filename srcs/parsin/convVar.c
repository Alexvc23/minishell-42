/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convVar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:39:20 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/08 17:28:55 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* It takes as parameter a string and an index to start from, it loops
through the string up until stamble upon a matacharacter, returning
the number of elements counted */
int	ft_get_next_space(char *cmd, int index)
{
	int	i;

	i = index;
	while (cmd[i] != '\0' && cmd[i] != ' ' && cmd[i] != '?'
		&& cmd[i] != '$' && cmd[i] != '"' && cmd[i] != '\'')
		i++;
	return (i);
}

/* 
works along side ft_cut_var, extracs any alphanumeric word up unstil 
metacharacter found
 */
char	*ft_get_first_quotes(char *cmd_b)
{
	int	i;

	i = 0;
	while (cmd_b[i] && cmd_b[i] != ' ' && cmd_b[i] != '$' && cmd_b[i] != '\n'
		&& ft_var_quotes(cmd_b, i, 1) == 0)
		i++;
	return (ft_substr(cmd_b, 0, i));
}

/* 
This function works just for variables expantion, 
-> if any substring after variable, store it in tempEnd
example: "hola $var como estan?"
result:  "como estan?" 
-> extract substring after metacaracter $, storing it in result
example: "hola $var como estan?"
result: "var"
*/
void	ft_cut_var(int i, char **result, char **tempEnd)
{
	*tempEnd = ft_substr(*result, ft_get_next_space(*result, \
		i + 1), ft_strlen(*result) - ft_get_next_space(*result, i));
	*result = ft_get_first_quotes(*result + i + 1);
}

/* 
->checks if we have to expand variables in line passed, if the variable
is exported in the enviroment variables, we replace the variable by
is value in the enviroment structure.
-> if we passed the variable '$?', it replace it with the last comand
return status number (0 for success >0 for error)
 */
char	*ft_with_var(char *brut, char *tempStart, char *tempEnd, int i)
{
	char	*result;
	char	*temp_result;

	result = ft_strdup(brut);
	while (result[i])
	{
		if (ft_check_is_var(result, i) == 1)
		{
			ft_set_start(&result, i, &tempStart);
			if (result[i + 1] == '?')
			{
				temp_result = ft_own_strjoin(tempStart,
						ft_itoa(g_vars->status));
				ft_set_temp_end(&result, i, &tempEnd);
			}
			else
			{
				ft_cut_var(i, &result, &tempEnd);
				ft_set_temp_result(&result, &tempStart, &temp_result);
			}
			ft_rest_while(&tempEnd, &i, &result, &temp_result);
		}
		i++;
	}
	return (result);
}

char	*ft_own_strjoin(char *s1, char *s2)
{
	char	*result;
	int		size;

	if (!s1 && !s2)
		return (ft_strdup("  "));
	else if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	result = malloc(size + 1);
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	ft_memcpy(result, s1, ft_strlen((char *)s1));
	ft_memcpy(result + ft_strlen((char *)s1), s2, ft_strlen((char *)s2));
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	return (result);
}
