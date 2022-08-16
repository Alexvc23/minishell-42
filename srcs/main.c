/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:56:37 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/15 21:45:09 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int event(void) 
{
	int result;

	rl_done = 1;
	result = RL_STATE_INITIALIZED;
	printf("%d\n %d\n", rl_done, result);
	return (0);
}

void	clear_exit(void)
{
	reset_terminal(g_vars);
	ft_free_env(g_vars->env);
	free(g_vars);
	ft_putstr_fd("\n", 1);
	exit(0);
}
/* 
Function called by signal SIGINT(interrupt from keyboard) in main program
this will mimic shell prompt behavior

SIGQUIT will do nothing just refresh view
*/

void	handler(int status)
{
	if (status == SIGINT)
	{
		if (!ft_strncmp(rl_prompt, "\033[31mHEREDOC", 11))
		{
			rl_signal_event_hook = event;
			rl_replace_line("", 0);
			return ;
		}
		else if(!ft_strcmp2(rl_prompt, "\033[1m\033[35mMinishell_> \033[0m"))
		{
			rl_redisplay();
			rl_replace_line("", 0);
			write(1, "\n", 1);
		}
	}
	else if (status == SIGQUIT)
	{
		rl_redisplay();
		if (rl_end > 0)
			clear_exit();
		return;
	}

	rl_on_new_line();
	rl_redisplay();
}

/* infinite loop receiving input, it checks commands followed by white space
   characters, if there is only spaces nothing is passed, otherwise we add the
   line to history, then we try to execute the command */
void	ft_prompt(void)
{
	char 	*entry;
	int		i;

	i = 0;
	rl_on_new_line();
	entry = ft_strdup(readline("\033[1m\033[35mMinishell_> \033[0m"));
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
	g_vars->env = ft_set_env(env);
	ft_termios();
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
		ft_prompt();
	return (0);
}