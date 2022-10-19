/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:38:25 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/18 16:19:26 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_vars->h_pid)
			kill(g_vars->h_pid, 15);
	}
}

/** 
	@brief Do variable explantion if heredoc delimiter is not surrounded 
	in single quotes 
	1. if heredoc demiter is not quoted we search for variables in t_env
	structure and we expand it in current line
	2. else join current line with the previous one if any, storing it in final
	3. free unnecessary variables
	4. return final
**/
char	*ft_set_s(char *line, char *previous, int isInquote)
{
	char	*temp;
	char	*final;
	char	*temp2;

	temp2 = NULL;
	temp = NULL;
	final = NULL;
	if (isInquote == 0)
	{
		temp2 = ft_with_var(line, NULL, NULL, 0);
		temp = ft_strjoin(temp2, "\n");
	}
	else
		temp = ft_strjoin(line, "\n");
	if (previous)
		final = ft_strjoin(previous, temp);
	else
		final = ft_strdup(temp);
	free(temp);
	if (temp2)
		free(temp2);
	if (previous)
		free(previous);
	return (final);
}

/**
	@brief Looks for quotes in the heredoc delimiter, retourn 1 if any found
**/
int	ft_quote_in_heredoc(char *end)
{
	int	i;

	i = 0;
	while (end[i])
	{
		if (end[i] == '\'' || end[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

/** 
	@brief checks if heredoc delimiter exists. 
	2. checks if there are quotes 
**/
void	ft_bool_heredoc(char **end, int i, int *bool_quote, char **result)
{
	if (!end[i] && !*result)
		*result = ft_strdup("");
	if (end[i])
		*bool_quote = ft_quote_in_heredoc(end[i]);
	else
		*bool_quote = 0;
}


/** 
    @brief
	1. we read from std input storinig it in a string using readline Function
	2. checks if **delimiter is sourrended by quotes
	3. As long as we haven't reached NULL in **delimiter variable, we check if
	we have to do a variable substitution with the help of function ft_set_s
	4. we free line variable beause we have now a new string called final_line
	being the result of the previous step and function ft_set_s
	5. we free temp being the result of end[i](**delimiter) without quotes
	we won't use it any more
	6. we free **end as we won't use it anymore, we have already determined a
	file descriptor
	7. Modify structure t_cmd, setting element struc->heredoc = 1, so 
	the execution part will know what to do
	8. we return the final_string contaning checked information to set it
	as input in t_cmd structure
**/

char	*ft_heredoc(char **end, t_cmd *stru, char *final_line)
{

	int		i;
	int		bool_quote;
	char	*line;
	char	*temp;

	i = 0;
	while (end[i])
	{
		line = readline("\033[31mHEREDOC\033[0m> ");
		if (!line )
			break ;
		temp = ft_gro_quotes(end[i]);
		if (!ft_strcmp2(line, temp))
			i++;
		ft_bool_heredoc(end, i, &bool_quote, &final_line);
		if (end[i])
			final_line = ft_set_s(line, final_line, bool_quote);
		free(line);
		free(temp);
	}
	ft_free((void **)end);
	end = NULL;
	stru->heredoc = 0;
	return (final_line);
}

static void ft_heredoc_child(char **end, t_cmd *stru, int files[2])
{
	char 	*final_line;

	final_line = NULL;
	final_line = ft_heredoc(end, stru, NULL);
	write(files[1], final_line, ft_strlen(final_line));
	if (final_line)
		free(final_line);
}

pid_t ft_heredoc_fork(char **end, t_cmd *stru)
{
	pid_t	pid;
	int		files[2];

	dup2(g_vars->stdin, STDIN_FILENO);
	if (pipe(files) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid)
	{
		dup2(files[0], STDIN_FILENO);
		close(files[0]);
		close(files[1]);
		return (pid);
	}
	ft_heredoc_child(end, stru, files);
	return(pid);
}

int wait_heredoc(char **end, t_cmd *stru)
{
	int status;
	reset_terminal(g_vars);
	// ft_termios();
	signal(SIGINT, ft_heredoc_handler);
	g_vars->h_pid = ft_heredoc_fork(end, stru);
	if (g_vars->h_pid == 0)
		exit(0);
	waitpid(g_vars->h_pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_vars->status = WEXITSTATUS(status);
		return (status);
	}
	else if (WIFSIGNALED(status))
	{
		g_vars->status = 2;
		return (7);
	}
	return (0);
}

int	ft_open(int mode, char *path)
{
	int	is_open;

	if (mode == 2)
		is_open = open(path, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		is_open = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	return (is_open);
}