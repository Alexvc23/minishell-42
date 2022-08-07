/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:56:37 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/07 17:21:40 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* Function called by signal SIGINT(interrupt from keyboard) in main program
   this will mimic shell prompt behavior */
void	handler(int status)
{
	if (status == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "^C\n", sizeof("^C\n"));
	}
	rl_on_new_line();
	rl_redisplay();
	/* we need to implement sigquit in this part */
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
	signal(SIGQUIT, handler); //we need to create it
	ft_termios();
	while (1)
		ft_prompt();
	return (0);
}
