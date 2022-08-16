/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 08:16:52 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/04 16:14:10 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
-->	Checks what kind of execution mode we are going to use, whether (cmd in 
	heredoc mode, cmd in single mode or multy pipe cmd), passing env as one 
	of the arguments to be use in case of builtin cmd present

--> we set this function as static as we won't get out of this scope file

--> It retunrs a pid_t which is the proccess id that we will use later on
	with the function waitpid()
*/
static pid_t	exec_type(t_cmd *cmd, t_env **env, int id)
{
	int	pid;

	if (cmd->heredoc)
		pid = exec_heredoc(cmd);
	if (!cmd->next)
	{
		dup2(g_vars->stdout, STDOUT_FILENO);
		pid = exec_single(cmd, env, id);
		dup2(g_vars->stdin, STDIN_FILENO);
		return (pid);
	}
	return (exec_pipe(cmd, env));
}

/* 
	The waitpid() system call suspends exection of the calling thread until 
	a child specified by pid argument has chnaged state.

--> WIFEXITED(wstatus) returns true if the child terminated normally,
	that is, by calling exit(3) or _exit(2), or by returning from main().

--> WEXITSTATUS(wstatus) returns the exit status of the child. This consists
	of the least significant 8 bits of the status argument that the child 
	specified in a call to exit(3) or _exit(2) or as the

--> WIFSIGNALED(wstatus) returns true if the child process was terminated by 
	a signal.

--> WTERMSIG(wstatus) returns the number of the signal that caused the child 
	process to terminate. this macro should be employed only if WIFSIGNALED
	returnd true.
*/
static void	exec_wait(t_cmd *cmd, unsigned int cmdsize)
{
	int				status;
	unsigned int	i;

	if (cmdsize > 1 || (cmd && !ft_is_builtin(cmd)))
	{
		i = -1;
		while (++i < cmdsize)
			waitpid(g_vars->pids[i], &status, 0);
		if (WIFEXITED(status))
			g_vars->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			printf("%d\n", WTERMSIG(status));
			g_vars->status = 128 + WTERMSIG(status);
		}
	}
	g_vars->pid_count = 0;
	free(g_vars->pids);
}

/* 
--> Sets pids array length  which will be used to store each process id
	and use it later on 

--> executes cmd taking into account its type

--> update env struct element "_" which is the last cmd executed 

--> Waits for every child

--> free resources, reset std-in-out default fds
*/
void	exec(t_cmd	*cmd)
{
	int				i;
	int				cmdsize;
	t_cmd			*backup;

	backup = cmd;
	i = -1;
	cmdsize = ft_size_list2(cmd);
	g_vars->pid_count = cmdsize;
	g_vars->pids = calloc(cmdsize, sizeof(int));
	if (!cmd || !cmdsize || !g_vars->pids)
		return ;
	while (++i < cmdsize)
	{
		g_vars->pids[i] = exec_type(cmd, &g_vars->env, i);
		if (cmd->next)
			cmd = cmd->next;
	}
	i = -1;
	while (cmd->argv[++i] && cmd->argv[i + 1]);
	ft_update_env(&g_vars->env, ft_strdup("_"), ft_strdup(cmd->argv[i]));
	exec_wait(backup, cmdsize);
	ft_free_cmd(backup);
	dup2(g_vars->stdin, STDIN_FILENO);
	dup2(g_vars->stdout, STDOUT_FILENO);
	dup2(g_vars->stderr, STDERR_FILENO);
}
