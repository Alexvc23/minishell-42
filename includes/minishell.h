/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:38:10 by jvalenci          #+#    #+#             */
/*   Updated: 2022/05/28 17:17:00 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
/* readline */

#include<stdlib.h>
/* Malloc, calloc, free */

#include <termios.h>
/*tcgetattr, tcsetattr */

#include <unistd.h>
/* write */

#include <signal.h>
/*signal*/

#include <readline/readline.h>
/* rl_replace_line rl_on_new_line rl_redisplay */

#include <readline/history.h>
/* readline */

#include"../libft/includes/libft.h"

//
// ─── STRUCTURES ───────────────────────────────────────────────
//

/* linked list where we will store all environment variables
key representing the variable name and value of the path*/

typedef struct s_env
{		
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* As minishell will create sub-processes, only global variables will be
inherited by child processes, we need to have access to these variables to create 
our own environment */
typedef struct s_shell {
	int				stdin;
	int				stdout;
	int				stderr;
	int				status;
	struct termios	term_save;
	int				pid_count;
	int				*pids;
	t_env			*env;
}	t_shell;

/* linked list representing each cmd passed with its arguments if there are.
Additionally, information about whether the input will be received in heredoc
mode and whether output file will be in append mode */ 

typedef struct s_cmd {
	char			*in;
	char			*out;
	int				heredoc;
	int				append;
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;

/* We make t_shell global variable */
t_shell	*g_vars;

//
// ─── FUNCTIONS ──────────────────────────────────────────────────────────────────
//

void reset_the_terminal(t_shell *t);
void   ft_termios();

// builtins
int	echo(char **argv);


#endif