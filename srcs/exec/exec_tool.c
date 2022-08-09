/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:55:22 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/09 15:20:44 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp2(cmd->argv[0], "echo"))
		return (1);
	if (!ft_strcmp2(cmd->argv[0], "export"))
		return (1);
	if (!ft_strcmp2(cmd->argv[0], "unset"))
		return (1);
	if (!ft_strcmp2(cmd->argv[0], "env"))
		return (1);
	if (!ft_strcmp2(cmd->argv[0], "pwd"))
		return (1);
	if (!ft_strcmp2(cmd->argv[0], "cd"))
		return (1);
	if (!ft_strcmp2(cmd->argv[0], "exit"))
		return (1);
	return (0);
}

/* 
dup_redirec checks if we have passed a file to the element (in) in the structure
t_cmd, if yes it sets it to as std_input, the same with cmd->out if there is 
something in this element it sets it as std_out
*/
void	dup_redirec(t_cmd *cmd)
{
	int	in;
	int	out;

	if (cmd->in && !cmd->heredoc)
	{
		in = open(cmd->in, O_RDONLY, 0777);
		if (in < 0)
			exit(1);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (cmd->out)
	{
		out = open(cmd->out, O_WRONLY | O_CREAT | (
					O_TRUNC * (cmd->append != 2)) | (
					O_APPEND * (cmd->append == 2)), 0777);
		if (out < 0)
			exit(1);
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}
