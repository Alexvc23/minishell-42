/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:54:35 by jvalenci          #+#    #+#             */
/*   Updated: 2022/07/07 22:54:44 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* 
count number of argument without main cmd
Algorithim: count increases everytime we find a character followed by a space  
checking is not surranded by quotes 
*/

int	ft_count_args(char *b_cmd, int i)
{
	int	count;

	count = 0;
	while (b_cmd[i])
	{
		if (i > 0 && b_cmd[i - 1] && (b_cmd[i - 1] == ' '
				&& ft_var_quotes(b_cmd, i - 1, 0) == 0) && b_cmd[i] != ' '
			&& b_cmd[i] != '-')
		{
			count++;
			i++;
		}
		else if (b_cmd[i] == '-' && ft_var_quotes(b_cmd, i, 0) == 0)
		{
			i++;
			while (b_cmd[i] && (b_cmd[i] != '\0'
					&& b_cmd[i] != ' ' && b_cmd[i] != '\n'))
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

int	ft_check_args(char *b_cmd, int i)
{
	if ((i > 0 && b_cmd[i - 1] && (b_cmd[i - 1] == ' '
				&& ft_var_quotes(b_cmd, i - 1, 0) == 0)
			&& b_cmd[i] != ' ' && b_cmd[i] != '-'))
		return (1);
	return (0);
}

int	ft_dash_args(char *b_cmd, int i)
{
	if (b_cmd[i] == '-' && ft_var_quotes(b_cmd, i, 0) == 0)
		return (1);
	return (0);
}

char	**ft_conv_args(char *b_cmd)
{
	char	**args;
	int		i;
	int		y;
	int		start;

	y = 1;
	i = 0;
	args = malloc(sizeof(char *) * (ft_count_args(b_cmd, 0) + 2));
	while (b_cmd[i])
	{
		if (ft_check_args(b_cmd, i) == 1 || ft_dash_args(b_cmd, i) == 1)
		{
			start = i;
			while (b_cmd[i] && (b_cmd[i] != '\0' && (b_cmd[i] != ' ' || \
				ft_var_quotes(b_cmd, i, 0) == 1) && b_cmd[i] != '\n'))
				i++;
			args[y] = ft_substr(b_cmd, start, i - start);
			y++;
		}
		else
			i++;
	}
	args[y] = NULL;
	return (args);
}