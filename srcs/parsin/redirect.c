/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:26:23 by jvalenci          #+#    #+#             */
/*   Updated: 2022/07/07 22:56:36 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
->	checks if metacharacter '>' is found and it is not surrounded by quotes 
->	store substring after '>' redirection character into path (file) and 
	set append mode in mode variable
 */
int	ft_redirec_output(char *cmd, t_cmd *stru, char *path, int mode)
{
	int	i;
	int	is_open;

	is_open = -1;
	i = 0;
	while (cmd[i])
	{
		if (is_open > 0)
			close(is_open);
		if (cmd[i] == '>' && ft_var_quotes(cmd, i, 0) == 0)
		{
			ft_cut_re(&mode, &path, &i, cmd);
			is_open = ft_open(mode, path);
			if (is_open < 0)
			{
				ft_putstr_fd(path, 2);
				ft_putstr_fd(" : Cannot access file or directory\n", 2);
				return (-1);
			}
		}
		i++;
	}
	stru->append = mode;
	stru->out = path;
	return (mode);
}

/* 
Checks whether we are using heredoc mode, if yes, it stores the 
the string representating the end of file in heredoc variable, which is 
passed as reference
*/
int	ft_is_heredoc(char *cmd, char ***heredoc, int *i, char *path)
{
	if (path)
		free(path);
	if (cmd[*i + 1] && cmd[*i + 1] == '<')
	{
		*heredoc = ft_alloc_delimiter(*heredoc, ft_get_afterre(cmd, *i + 1, 1));
		*i += 2;
		return (1);
	}
	return (0);
}

/* 
   Opens normal file if passed as input redirection, checking if no erros
-> it fills path with the argument temp
-> stores file descriptor in is_open
-> returns -1 if error 0 if sucess
*/
int	ft_normal_file(int *mode, char **path, int *is_open, char **temp)
{
	*mode = 1;
	*path = ft_gro_quotes(*temp);
	*is_open = open(*path, O_RDONLY);
	if (*is_open < 0)
	{
		ft_putstr_fd(*path, 2);
		ft_putstr_fd(" : Cannot access file or directory\n", 2);
		return (-1);
	}
	if (*temp)
		free(*temp);
	*temp = NULL;
	return (0);
}

/* 
This function will determine which file descriptor will be set as
stdinput, (whether heredoc or normal) file inicializating the t_cmd
structure, returns append mode number or a negatif number representing
error
*/
int	ft_end_rre(char **heredoc, t_cmd *stru, char *path, int mode)
{
	char	*temp;

	temp = NULL;
	if (heredoc)
	{
		temp = ft_heredoc(heredoc, stru, NULL);
		if (!temp)
			return (-2);
		stru->in = temp;
	}
	else
		stru->in = path;
	stru->append = mode;
	return (mode);
}

/* 
Checks if we are passing (less than metacharacter '<') that means redirection
input.
-> if heredoc is foud, it calls function ft_is_heredoc, which is in charge of
storing string heredoc delimiter in **heredoc variable, extracting 
delimiter from notVar.
-> if a normal file is provided as input, it call fuction ft_normal_file, that
will open the file if exits, storing its file descriptor in is_open variable 
and path in path variable
-> if is_open file descriptor is open we close it, as we did it just for 
testing file existance with function ft_is_normal_file 
-> finally  once ends the loop itiration ft_end_rre function will determine 
what the descriptor to user:
1) if something in heredoc, it will use ft_is_heredoc setting heredoc as 
stdinput.
2) else it will user path as file descriptor, if there is nothing in path 
    stdin will be set to null
*/
int	ft_redirec_input(char *cmd, t_cmd *stru, char *notVar, int mode)
{
	int		i;
	int		is_open;
	char	**heredoc;
	char	*temp;
	char	*path;

	path = NULL;
	i = -1;
	heredoc = NULL;
	temp = NULL;
	is_open = -1;
	while (cmd[++i])
	{
		if (is_open > 0)
			close(is_open);
		if (cmd[i] == '<' && ft_var_quotes(cmd, i, 0) == 0)
		{
			if (ft_is_heredoc(notVar, &heredoc, &i, path) == 1)
				continue ;
			temp = ft_get_afterre(cmd, i, 0);
			if (ft_normal_file(&mode, &path, &is_open, &temp) == -1)
				return (-1);
		}
	}
	return (ft_end_rre(heredoc, stru, path, mode));
}