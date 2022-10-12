/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:34:15 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/12 15:58:50 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#define CD_ABSOLUTE 1
#define CD_OLD 2
#define CD_HOME_AND_PATH 3
#define CD_HOME 4 
#define CD_CURREN_AND_PATH 5
#define ERR_SIG 7

/* readline */
#include <stdio.h>

/* Malloc, calloc, free */
#include<stdlib.h>

/*tcgetattr, tcsetattr */
#include <termios.h>

/* stat */
/* write */
/* chdir */
#include <unistd.h>

/*signal*/
#include <signal.h>

/* rl_replace_line rl_on_new_line rl_redisplay */
#include <readline/readline.h>

/* readline */
#include <readline/history.h>

/* stat */
#include<sys/stat.h>

/* stat */
#include<sys/types.h>

/* Error handling */
# include <errno.h>

/* wait */
#include <sys/wait.h>

#include <fcntl.h>

#include"../libft/includes/libft.h"

//
// ─── STRUCTURES ───────────────────────────────────────────────
//

typedef struct	s_heredoc 
{
	int		i;
	int		is_open;
	pid_t	pid;
	char	**heredoc;
	char	*temp;
	char	*path;
}				t_heredoc;


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
	struct termios	term_new;
	char			*entry;
	int				pid_count;
	int				*pids;
	pid_t				h_pid;
	t_env			*env;
}	t_shell;

/* We make t_shell global variable */
t_shell	*g_vars;

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

//
// ─── FUNCTIONS ──────────────────────────────────────────────────────────────────
//

/* parsing */
t_env	*ft_set_env(char **argv);
t_cmd	*ft_parse_cmd(char *line);
void	ft_create_tokens(char *cmd_b, t_cmd *cmd);
int		ft_redirec_output(char *cmd, t_cmd *stru, char *path, int mode);
int		ft_redirec_input(char *cmd, t_cmd *stru, char *notVar, int mode);
char	**ft_conv_args(char *b_cmd);
char	*ft_own_strjoin(char *s1, char *s2);
char	*ft_with_var(char *brut, char *tempStart, char *tempEnd, int i);
void	ft_cut_re(int *mode, char **path, int *i, char *cmd);
char	*ft_heredoc(char **end, t_cmd *stru, char *final_line);
int		wait_heredoc(char **end, t_cmd *stru);

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
void	ft_join_temp_end(char **tempEnd, int *i, char **result, char **tempResult);
void	without_quote_args(t_cmd *env);
int		ft_get_next_space(char *cmd, int index);

/* check */
void    ft_check_quotes(char *line);
void    ft_check_pipe(char *line);
void    ft_check_redir(char *line);

/* I/O  */
void	reset_terminal(t_shell *t);
void	ft_termios();

// builtins
int		ft_cd(char **argv, t_env **env);
int		ft_echo(char **argv);
int		ft_env(t_env **env);
int		ft_pwd(t_env **env);
int		ft_exit(t_cmd *cmd);
int		ft_unset(char **argv, t_env **env);
int		ft_export(char **argv, t_env **env);
void	ft_set_env2(t_env **env, char *key, char *value);
char	*ft_get_env(t_env *env, char *key);
void	ft_afree(void **arr);
char	**ft_env_to_key_array(t_env **env);
int		ft_is_valid_key(char *key);

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
void	ft_free_cmd(t_cmd *cmd);
char	*ft_env_join(char *key, char *value);
char	**ft_env_to_array(t_env **env);
char	*ft_find_path(char **env);
char	*ft_get_cmd(char *v_path, char *cmd);
int		ft_is_builtin(t_cmd *cmd);
void	ft_free_env(t_env *env);
int		ft_strequ(char *s1, char *s2);
void	hide_sig(int sig);
int		ft_increase_shlvl(t_env	*env);
t_heredoc *inicialize_heredoc(void);
int		ft_counter(t_cmd	*cmd);

// EXECUTION
void		exec(t_cmd	*cmd);
pid_t		exec_pipe(t_cmd *cmd, t_env **env);
pid_t		exec_single(t_cmd *cmd, t_env **env, int id);
pid_t		exec_heredoc(t_cmd *cmd);
void		dup_redirec(t_cmd *cmd);
int			ft_is_builtin(t_cmd *cmd);

#endif