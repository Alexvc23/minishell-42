/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:38:10 by jvalenci          #+#    #+#             */
/*   Updated: 2022/06/14 12:00:01 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#define CD_NORMAL 1
#define CD_OLD 2
#define CD_PATH_HOME 3

#include <stdio.h>
/* readline */

#include<stdlib.h>
/* Malloc, calloc, free */

#include <termios.h>
/*tcgetattr, tcsetattr */

#include <unistd.h>
/* stat */
/* write */
/* chdir */

#include <signal.h>
/*signal*/

#include <readline/readline.h>
/* rl_replace_line rl_on_new_line rl_redisplay */

#include <readline/history.h>
/* readline */

#include<sys/stat.h>
/* stat */

#include<sys/types.h>
/* stat */


#include"../libft/includes/libft.h"

//
// ─── STRUCTURES ───────────────────────────────────────────────
//

/* linked list where we will store all environment variables
key representing the variable name and value the path*/

typedef struct s_env
{		
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* As minishell will create sub-processes, only global variables
 will be inherited by child processes, we need to have access to
 these variables to create our own environment */
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

/* linked list representing each cmd passed with its arguments if
there are. Boolean checking heredoc mode, output file append mode,
 and input file or output file path if ther is one */

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

/* parsing */
t_env	*ft_set_env(char **argv);

/* check */
void    ft_check_quotes(char *line);
void    ft_check_pipe(char *line);
void    ft_check_redir(char *line);

/* I/O  */
void	reset_the_terminal(t_shell *t);
void   ft_termios();

// builtins
int		ft_cd(char **argv, t_env **env);
int		ft_echo(char **argv);
void	ft_env(t_env *env);

// tools
void	ft_add_node_back(t_env **head, t_env *new);
t_env	*ft_new_node(char *key, char *value);
void	ft_replase_nv(t_env **env, char *key, char *value);
int		ft_size_list(t_env *head);
t_env	*ft_last_node(t_env *head);
void	ft_update_env(t_env **env, char *key, char *value);
char	*ft_get_node_value(t_env **head, char *key);
void	ft_update_env(t_env **env, char *key, char *value);
int		ft_strcmp2(char *s, char *s1);
int		ft_charcnt(char *str, char c);

#endif