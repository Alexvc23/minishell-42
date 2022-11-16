/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:38:25 by jvalenci          #+#    #+#             */
/*   Updated: 2022/11/16 18:49:11 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*ft_heredoc(char **end, t_cmd *stru, char *final_line)
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

static char *ft_heredoc_child(char **end, t_cmd *stru)
{
	char 	*final_line;
	char	*result;

	final_line = NULL;
	ft_termios();
	final_line = ft_heredoc(end, stru, NULL);
	reset_terminal();
	result = ft_strjoin(final_line , "\0");
	if (final_line)
		free(final_line);
	return (result);
}

static int wait_heredoc(t_cmd *stru, int files[2])
{
	int status;

	if (wait(&status) < 0)
	{
		kill(g_vars->h_pid, SIGTERM);
		return (-1);
	}
	if (WIFEXITED(status))
		g_vars->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		printf("passing WIFSIGNALED \n");
		g_vars->status = 1;
		return (-1);
	}
	g_vars->h_pid = 0;
	stru->heredoc_in = get_file_text(files[0]);
	return (status);
}

pid_t ft_heredoc_fork(char **end, t_cmd *stru)
{
	int		files[2];
	int		status;
	char 	*buffer;

	status = 0;
	stru->heredoc = 1;
	if (pipe(files) < 0)
		return(-1);
	g_vars->h_pid = fork();
	if (g_vars->h_pid < 0)
		return (-1);
	if (!g_vars->h_pid)
	{
		buffer = ft_heredoc_child(end, stru);
		write(files[1], buffer, ft_strlen(buffer));
		close(files[1]);
		close(files[0]);
		exit(0);
	}
	close(files[1]);
	status = wait_heredoc(stru, files);
	close(files[0]);
	ft_free((void **)end);
	return (status);
}