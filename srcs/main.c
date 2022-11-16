/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:56:37 by jvalenci          #+#    #+#             */
/*   Updated: 2022/11/14 19:10:25 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	clear_exit(void)
{
	reset_terminal();
	ft_free_env(g_vars->env);
	ft_putstr_fd("exit", 1);
	free(g_vars);
	exit(0);
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
	entry = readline("Minishell >");
	reset_terminal();
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
	if (!g_vars)
		return (write(3, "Error allocating memory\n", 25));
	g_vars->stdin = dup(STDIN_FILENO);
	g_vars->stdout = dup(STDOUT_FILENO);
	g_vars->stderr = dup(STDERR_FILENO);
	g_vars->env = ft_set_env(env);
	g_vars->h_pid = 0;
	// ft_update_env(&g_vars->env, ft_strdup("SHLVL"),
	// 	ft_itoa(ft_increase_shlvl(g_vars->env)));
	while (1)
		ft_prompt();
	
	return (0);
}
