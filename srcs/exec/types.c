/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:54:48 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/08 17:31:12 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(t_cmd *cmd, t_env **env)
{
	// if (cmd->argv[0][0] == 1)
	// 	return (ft_null());
	// else if (ft_strcmp2(cmd->argv[0], "exit"))
	// 	return (ft_exit(cmd));
	if (ft_strcmp2(cmd->argv[0], "echo"))
		return (ft_echo(cmd->argv));
	// else if (ft_strcmp2(cmd->argv[0], "export"))
	// 	return (ft_export(cmd->argv, env));
	// else if (ft_strcmp2(cmd->argv[0], "unset"))
	// 	return (ft_unset(cmd->argv, env));
	else if (ft_strcmp2(cmd->argv[0], "env"))
		return (ft_env(env));
	else if (ft_strcmp2(cmd->argv[0], "pwd"))
		return (ft_pwd(env));
	else if (ft_strcmp2(cmd->argv[0], "cd"))
		return (ft_cd(cmd->argv, env));
	return (1);
}

/* 
--> This function will be used as  complement for all execution types 
	(heredoc, single and pipe) and it will be executed as a child process 

--> we can execute built-ins as children processes

--> Turns env structure elements to 2D array represeting new env array
	that will be used by all the built-ins

--> handles exit status: 
		if a command is not found, the child process created to execute 
		it returns a status of 127, if a command is found but is not
		executable, the returns status is 126

		otherwise we set the exit status to the number store in errno which
		was set by execve

		https://www.gnu.org/software/bash/manual/html_node/Exit-Status.html
		https://www.thegeekstuff.com/2010/10/linux-error-codes/
*/
static void	exec_cmd(t_cmd *cmd, t_env **env)
{
	char	**arr_env;
	char	*path_cmd;

	// if (ft_is_builtin(cmd))
	// 	exit(exec_builtin(cmd, env));
	arr_env = ft_env_to_array(env);
	path_cmd = ft_get_cmd(ft_find_path(arr_env), cmd->argv[0]);
	execve(path_cmd, cmd->argv, arr_env);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (errno != 2 || (ft_strchr(cmd->argv[0], '/')))
		printf("%s: %s.\n", cmd->argv[0], strerror(errno));
	else
		printf("Command '%s' not found.\n", cmd->argv[0]);
	dup2(g_vars->stdout, STDOUT_FILENO);
	free(path_cmd);
	ft_free((void **)arr_env);
	if (errno == 2 || errno == EACCES)
		exit((errno == 2) * 127 + (errno == EACCES) * 126);
	exit(1);
}

/* 
if cmd is a built-in, it will be executed by the parent process to have
the changes permanently reflected 
*/
pid_t	exec_single(t_cmd *cmd, t_env **env, int id)
{
	pid_t	pid;

	if (id == 0 && ft_is_builtin(cmd))
	{
		dup_redirec(cmd);
		g_vars->status = exec_builtin(cmd, env);
		dup2(g_vars->stdin, STDIN_FILENO);
		dup2(g_vars->stderr, STDERR_FILENO);
		dup2(g_vars->stdout, STDOUT_FILENO);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid)
		return (pid);
	dup_redirec(cmd);
	exec_cmd(cmd, env);
	return (pid);
}

/*
--> For every interation, we will inicilize a pipe, setting in the parent
	process the file descriptor that will be used as STDIN in the next 
	pipe(cmd) execution

--> exec_dup checks if there is a input or output redirection to set as 
STD-IN-OUT 

--> During the child execution we will take the default 
	STDIN(during first iteration) or the one set by parent process during 
	last execution and set index 1 of pipe as STDOUT, like that we are 
	conneting the result of the current execution with the next command if 
	there is one.
 */
pid_t	exec_pipe(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		files[2];

	if (pipe(files) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid)
	{
		dup2(files[0], STDIN_FILENO);
		close(files[0]);
		close(files[1]);
		return (pid);
	}
	dup2(files[1], STDOUT_FILENO);
	close(files[0]);
	close(files[1]);
	dup_redirec(cmd);
	exec_cmd(cmd, env);
	return (pid);
}
