/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:33:35 by alexanderva       #+#    #+#             */
/*   Updated: 2022/11/15 09:35:04 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
		kill(g_vars->h_pid, SIGTERM);
}

/*
Function called by signal SIGINT(interrupt from keyboard) in main program
this will mimic shell prompt behavior

SIGQUIT will do nothing just refresh view
*/

static void	shell_handler(int status)
{
	if (g_vars->pid_count > 0)
		return;
	if (status == SIGINT && g_vars->h_pid == 0)
	{
			rl_redisplay();
			rl_replace_line("", 0);
			write(1, "\n", 1);
	}
	else if (status == SIGQUIT)
	{}
	rl_on_new_line();
	rl_redisplay();
}

void handler(int status)
{
	printf("h_pid: %d\n", g_vars->h_pid);
	if (g_vars->h_pid == 0)
	{
		shell_handler(status);
	}
	else
	{
		heredoc_handler(status);
	}
}