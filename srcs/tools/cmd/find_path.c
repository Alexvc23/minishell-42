/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:33:13 by jvalenci          #+#    #+#             */
/*   Updated: 2022/11/16 18:30:37 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
Fetchs variable path from env
*/
char	*ft_find_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			return (env[i] + 5);
	}
	return (NULL);
}

/* 
Returns the path of a specific command
*/
char	*ft_get_cmd(char *v_path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*new_cmd;
	char	**path;

	i = -1;
	if (!cmd || !cmd[0])
		exit(0);
	if (!v_path || (ft_strchr(cmd, '/') && !access(cmd, 0)))
		return (cmd);
	path = ft_split(v_path, ':');
	while (path && path[++i])
	{
		tmp = ft_strjoin("/", cmd);
		new_cmd = ft_strjoin(path[i], tmp);
		if (!access(new_cmd, 0))
		{
			free(tmp);
			return (new_cmd);
		}
		free(tmp);
		free(new_cmd);
	}
	if (!v_path || access(cmd, 0) == 0)
		return (cmd);
	return (cmd);
}