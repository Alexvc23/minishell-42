/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:06:37 by jvalenci          #+#    #+#             */
/*   Updated: 2022/11/16 19:00:54 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_inicialize_cmd(t_cmd *cmd)
{
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->heredoc = 0;
	cmd->heredoc_in = NULL;
	cmd->append = 0;
	cmd->argv = NULL;
	cmd ->next = NULL;
}

/* 
-> Inicialize t_cmd
-> Create tokens
-> return t_cmd structure
*/
t_cmd	*ft_parse_cmd(char *line)
{
	g_vars->cmd = malloc(sizeof(t_cmd));
	if (!g_vars->cmd)
		return (NULL);
	ft_inicialize_cmd(g_vars->cmd);
	ft_create_tokens(line, g_vars->cmd);
	return (g_vars->cmd);
}
