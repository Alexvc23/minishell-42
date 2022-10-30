/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:55:22 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/25 14:50:03 by alexanderva      ###   ########.fr       */
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
	// char buffer[100];

	if (cmd->in && !cmd->heredoc)
	{
		in = open(cmd->in, O_RDONLY, 0777);
		if (in < 0)
			exit(1);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	else if (cmd->heredoc)
	{
		printf("heredoc\n");
		dup2(cmd->heredoc_file[0], STDIN_FILENO);
		// printf("%d\n", g_vars->h_files[0]);
		// read(g_vars->files[0], buffer, 100);
		// printf("%s\n", buffer);
		close(cmd->heredoc_file[0]);
		close(cmd->heredoc_file[1]);
		cmd->heredoc = 0;
	}
	if (cmd->out)
	{
		out = open(cmd->out, O_WRONLY | O_CREAT | (O_TRUNC * (cmd->append != 2)) 
		| (O_APPEND * (cmd->append == 2)), 0777);
		if (out < 0)
			exit(1);
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}
