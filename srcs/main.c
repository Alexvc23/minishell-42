/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:56:37 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/19 11:23:28 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	clear_exit(void)
{
	reset_terminal(g_vars);
	ft_free_env(g_vars->env);
	ft_putstr_fd("exit", 1);
	free(g_vars);
	exit(0);
}
/* 
Function called by signal SIGINT(interrupt from keyboard) in main program
this will mimic shell prompt behavior

SIGQUIT will do nothing just refresh view
*/

void	handler(int status)
{
	if (g_vars->pid_count > 0)
	{
		hide_sig(status);
		return ;
	}
	if (status == SIGINT)
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

/* infinite loop receiving input, it checks commands followed by white space
   characters, if there is only spaces nothing is passed, otherwise we add the
   line to history, then we try to execute the command */
void	ft_prompt(void)
{
	char	*entry;
	int		i;

	i = 0;
	ft_termios();
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	entry = readline("\033[1m\033[35mMinishell_> \033[0m");
	if (!entry)
		clear_exit();
	while (entry[i] && entry[i] == ' ')
		i++;
	if (entry[0] && (size_t)i < ft_strlen(entry))
	{
		add_history(entry);
		ft_check_quotes(entry);
	}
	else
		free(entry);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	g_vars = malloc(1 * sizeof(t_shell));
	g_vars->stdin = dup(STDIN_FILENO);
	g_vars->stdout = dup(STDOUT_FILENO);
	g_vars->stderr = dup(STDERR_FILENO);
	g_vars->h_pid = 0;
	g_vars->env = ft_set_env(env);
	ft_update_env(&g_vars->env, ft_strdup("SHLVL"),
		ft_itoa(ft_increase_shlvl(g_vars->env)));
	while (1)
		ft_prompt();
	return (0);
}
