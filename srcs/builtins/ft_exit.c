/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:25:13 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/18 19:07:56 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
https://www.gnu.org/software/bash/manual/bash.html#Bourne-Shell-Builtins
*/

static int	ft_strnum(char *str)
{
	int	i;

	if (!str)
		return (g_vars->status);
	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
	}
	return (ft_atoi(str) % 256);
}

int	ft_exit(t_cmd *cmd)
{
	int	status;

	status = ft_strnum(cmd->argv[1]);
	if (status != 255 && cmd->argv[1] && cmd->argv[2])   // all the subsecent arguments may leak ?
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return(1);
	}
	ft_free_cmd(cmd);
	free(g_vars->pids);
	reset_terminal(g_vars);
	ft_free_env(g_vars->env);
	free(g_vars);
	if (status != 255)
		ft_putstr_fd("exit\n", 1);
	exit(status);
}
