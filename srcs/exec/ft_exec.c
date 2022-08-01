/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 08:16:52 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/01 12:45:37 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//If the infile and outfile exist, they are linked togethers.
void	ft_exec_dup(t_cmd *cmd)
{
	int outfile;
	int	infile;

	if (cmd->in && !cmd->heredoc)
	{
		infile = open(cmd->in, O_RDONLY, 777);
		if (infile < 0)
			exit(1);
		dup2(infile, STDIN_FILENO)
		close(infile);
	}
	if (cmd->out)
	{
		outfile = (cmd->out, O_WRONLY | O_CREAT
			| (O_TRUNC * (cmd->append != 2)) | O_APPEND * (cmd->append == 2));
		if (outfile < 0)
			exit(1);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
}

// We run either in single cmd, multi pipe or cmd+heredoc

pid_t	ft_exec_single(t_pipestr	pstruct, t_cmd	*cmd, int id)
{
	pid_t	pid;

	if (id == 0 && ft_is_builtin(cmd))
	{
		ft_exec_dup(cmd);
		g_shell->status = ft_exec_builtin(cmd, env);
		dup2(g_shell->stdin, STDIN_FILENO);
		dup2(g_shell->stderr, STDERR_FILENO);
		dup2(g_shell->stdout, STDOUT_FILENO);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid)
		return (pid);
	ft_exec_dup(cmd);
	ft_exec_cmd(cmd, env);
	return (pid);
}


void ft_exec(t_cmd	*cmd)
{
	t_pipestr	pstruct;
	int			i;
	t_cmd		*save;

	save = cmd;
	pstruct.calls = ft_size_list2(cmd);
	pstruct.ids = malloc(pstruct.calls, sizeof(pid_t));
	if (!pstruct->ids || !cmd || !cmd->argv)
		return (-1);
	i = 0;
	// this will iterate through the whole list of args and execute them
	// one after the other while handling the pipe to connect them.
	while (i < pstruct.calls) 
	{
		pstruct->pids[i] = ft_exec_router(pstrcut, cmd, i);
		if (i < pstruct.calls - 1)
			cmd = cmd->next;
		i++;
	}
	//ft_update_env(cmd); TODO
	//ft_exec_wait(save, cmdsize); TODO
	pwrd_kill(&pstruct); //That should be ft_free_cmd()
	dup2(g_shell->stdout, STDOUT_FILENO);
	dup2(g_shell->stdin, STDIN_FILENO);
	dup2(g_shell->stderr, STDERR_FILENO);
}
