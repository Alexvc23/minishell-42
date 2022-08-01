/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 05:49:44 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/01 12:45:19 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//This is here only to help me get what was the example doing compared to my pipex project

#ifndef PIPEX_H
# define PIPEX_H

# include	"../r_toolbox/r_toolbox.h"
# include	<stdio.h>
# include	<errno.h>
# include	<unistd.h>
# include	<sys/wait.h>

typedef struct s_pipestr {
//	int		f1; cmd->in
//	int		f2; cmd->next->out
	int		tube[2];
	char	**paths;
//	char	**args1; cmd->argv
//	char	**args2; cmd->next->argv
	pid_t	child1;
	pid_t	child2;
	int		status;
	int		calls;
}	t_pipestr;

char	*strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*get_path(char **envp);
char	*address_maker(char *path, char **command);
int		pwrd_kill(t_pipestr *splbk);
int		free_one(char **stuff);
//int		open_sesame(t_pipestr	*splbk, char **argv);

#endif