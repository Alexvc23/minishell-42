/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:56:37 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/08 17:38:40 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	clear_exit(void)
{
	reset_terminal(g_vars);
	ft_putstr_fd("exit\n", 1);
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
		rl_replace_line("", 0);
		write(1, "^C\n", sizeof("^C\n"));
	}
	else if (status == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
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
	entry = readline("Minishell_> ");
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
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	ft_termios();
	while (1)
		ft_prompt();
	return (0);
}
