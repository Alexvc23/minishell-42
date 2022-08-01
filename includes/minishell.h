/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:38:10 by jvalenci          #+#    #+#             */
/*   Updated: 2022/07/03 11:51:20 by jvalenci         ###   ########.fr       */
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

/* 
linked list where we will store all environment variables
key representing the variable name and value the path
*/
typedef struct s_env
{		
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* 
As minishell will create sub-processes, only global variables
will be inherited by child processes, we need to have access to
these variables to create our own environment

-> stdio: new filde descriptor linked to standar input with dup
-> stdout: new filde descriptor linked to standar output with dup
-> stderr: new filde descriptor linked to standar error with dup
-> status: last command returned code executed in this shell
-> term_save: back up termios structure 
-> 
-> pids: children processes ids
-> env: link to evironment variables
*/
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

/* 
linked list representing each cmd passed with its arguments if
there are. Boolean checking heredoc mode, output file append mode,
and input file or output file path if ther is one
*/
typedef struct s_cmd {
	char			*in;
	char			*out;
	int				heredoc;
	int				append;
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;

// This is my old structure for pipex, I'm figuring out what 
// need to be removed from it as I'm adapting my pipex to this project

typedef struct s_spellbook {
//	int		f1;  cmd->in
//	int		f2;  cmd->next->out
	int		tube[2];
	char	**paths;
//	char	**args1; cmd->argv
//	char	**args2; cmd->next->argv
	pid_t	*ids;
	int		status;
}	t_spellbook;

/* We make t_shell global variable */
t_shell	*g_vars;



//
// ─── FUNCTIONS ──────────────────────────────────────────────────────────────────
//

/* parsing */
t_env	*ft_set_env(char **argv);
char	*ft_heredoc(char **end, t_cmd *stru, char *final_line);
t_cmd	*ft_parse_cmd(char *line);
void	ft_create_tokens(char *cmd_b, t_cmd *cmd);
int		ft_redirec_output(char *cmd, t_cmd *stru, char *path, int mode);
int		ft_redirec_input(char *cmd, t_cmd *stru, char *notVar, int mode);
char	**ft_conv_args(char *b_cmd);
char	*ft_own_strjoin(char *s1, char *s2);
char	*ft_with_var(char *brut, char *tempStart, char *tempEnd, int i);
void	ft_cut_re(int *mode, char **path, int *i, char *cmd);

/* parsing tools*/
int		ft_doublequotes(char *str, int index);
int		ft_singlequotes(char *str, int index);
char	*ft_gro_quotes(char *str);
int		ft_var_quotes(char *var, int index, int dollar);
char 	**ft_alloc_delimiter(char **result, char *value);
char  	*ft_get_afterre(char *cmd, int index, int heredoc);
char	**ft_split_token(char *s, char c);
int		ft_open(int mode, char *path);
char	*ft_skip_spaces(char *cmd_b);
void	ft_fill_err(t_cmd *cmd);
void	ft_free_multiple(char *one, char *two, char *tree, char *four);
char	*ft_conv_redir(char *cmd);
char	*ft_get_first(char *cmd_b);
void	ft_inicialize_cmd(t_cmd *cmd);
int		ft_check_is_var(char *result, int i);
void	ft_set_start(char **result, int i, char **tempStart);
void	ft_set_temp_end(char **result, int i, char **tempEnd);
void	ft_set_temp_result(char **result, char **tempStart, char **tempResult);
void	ft_rest_while(char **tempEnd, int *i, char **result, char **tempResult);
void	without_quote_args(t_cmd *env);
int	ft_get_next_space(char *cmd, int index);

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
void	ft_pwd(t_env *env);
void	ft_exit(int status, t_shell *vars);

// tools
void	ft_add_node_back(t_env **head, t_env *new);
t_env	*ft_new_node(char *key, char *value);
void	ft_replase_nv(t_env **env, char *key, char *value);
int		ft_size_list(t_env *head);
int		ft_size_list2(t_cmd *cmd);
t_env	*ft_last_node(t_env *head);
char	*ft_get_node_value(t_env **head, char *key);
void	ft_update_env(t_env **env, char *key, char *value);
int		ft_strcmp2(char *s, char *s1);
int		ft_charcnt(char *str, char c);

// exec


#endif