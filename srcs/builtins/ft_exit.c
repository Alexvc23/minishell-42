/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:25:13 by fdevigne          #+#    #+#             */
/*   Updated: 2022/10/20 18:53:44 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_strnum(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	if (!str)
		return (g_vars->status);
	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) || len > 19 || (len > 1 && ft_atoi(str) == 0))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required.\n", 2);
			return (255);
		}
	}
	ft_putstr_fd("exit\n", 1);
	return (ft_atoi(str) % 256);
}

/** 
	https://www.gnu.org/software/bash/manual/bash.html#Bourne-Shell-Builtins
	@return 255 if no numeric value provided, or 255 if integer overflow
	else (value % 256) is retuned 
**/
int	ft_exit(t_cmd *cmd)
{
	int	status;

	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("exit: too many arguments.\n", 2);
		return (1);
	}
	status = ft_strnum(cmd->argv[1]);
	ft_free_cmd(cmd);
	free(g_vars->pids);
	reset_terminal(g_vars);
	ft_free_env(g_vars->env);
	free(g_vars);
	exit(status);
}
