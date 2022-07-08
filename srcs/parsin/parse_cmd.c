/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:06:37 by jvalenci          #+#    #+#             */
/*   Updated: 2022/07/08 12:06:39 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void ft_inicialize_cmd(t_cmd *cmd)
{
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->heredoc = 0; 
	cmd->append = 0;
	cmd->argv = NULL;
	cmd ->next = NULL;;
}

/* 
-> Inicialize t_cmd
-> Create tokens
-> return t_cmd structure
*/
t_cmd *ft_parse_cmd(char *line)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_inicialize_cmd(cmd);
	ft_create_tokens(line, cmd);
	return (cmd);
}