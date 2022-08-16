/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:18:29 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/15 11:28:49 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* echo function with -n argument will skip \n at the end of line 
   addtionally, we handle error checking by allowing the argument -n
   as follow: "-nnnnnnnn" or "-nnnnn" -n -n -n -n -n -n.., this behavior
   should be accepted as an unique -n and skip \n at the end of argv. we
   won't accept the option -n if it is followed by anything different from 'n'
example: "-nnnnp" "-nnnnz" "-nnn " this will be printed as normal output */

int	ft_print(int i, int end_of_line, char **argv)
{
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], 1);
		write(1, " ", (argv[i] != NULL));
	}
	write(1, "\n", end_of_line);
	return (0);
}

int	ft_echo(char **argv)
{
	int	i;
	int	j;
	int	end_of_line;

	i = 1;
	j = 1;
	end_of_line = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		end_of_line = 0;
		while (argv[i][j])
		{
			if (argv[i][j] != 'n')
				end_of_line = 1;
			j++;
		}
		if (end_of_line)
			break ;
		i++;
	}
	return (ft_print(i, end_of_line, argv));
}
