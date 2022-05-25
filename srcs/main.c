/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:56:37 by jvalenci          #+#    #+#             */
/*   Updated: 2022/05/25 19:56:40 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* function called by signal SIGINT(interrupt from keyboard) this
will mimic shell prompt behavior */
void handler (int status)
{
if (status == SIGINT)
    {
        rl_replace_line("", 0);
        write(1, "^C\n", sizeof("^C\n"));
        rl_on_new_line();
        rl_redisplay();
    }
}

/* infinite loop receiving input and executing commands */
void    ft_prompt()
{
    char *entry;
    entry = readline("Minishell_Alex> ");
    free(entry);
}

int main (int argc, char** argv)
{
    (void)argc;
    (void)argv;
    g_vars = malloc(1 * sizeof(t_shell));
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    ft_termios();
    while (1)
        ft_prompt();
    free(g_vars);
    return (0);
}