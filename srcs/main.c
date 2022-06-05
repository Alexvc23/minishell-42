/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:56:37 by jvalenci          #+#    #+#             */
/*   Updated: 2022/06/05 10:42:14 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* Function called by signal SIGINT(interrupt from keyboard) in main program
this will mimic shell prompt behavior */
void handler (int status)
{
if (status == SIGINT)
    {
        rl_replace_line("", 0);
        write(1, "^C\n", sizeof("^C\n"));
        rl_on_new_line();
        rl_redisplay();
    }
/* we need to implement sigquit in this part */
}

/* infinite loop receiving input and executing commands */
void    ft_prompt()
{
    char *entry;
    entry = readline("Minishell_> ");
    free(entry);
}

int main (int argc, char** argv, char **env)
{
    (void)argc;
    (void)argv;
    g_vars = malloc(1 * sizeof(t_shell));
    g_vars->env = ft_set_env(env);
    signal(SIGINT, handler);
    signal(SIGQUIT, handler); //we need to create it
    ft_termios();
    while (1)
        ft_prompt();
    free(g_vars);
    ft_env(g_vars->env);
    return (0);
}