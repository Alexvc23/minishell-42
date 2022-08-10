/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:18:34 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/10 15:49:28 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* Allows to print error messages to stderr, customizing it's behavior
   whether printing a cmd error or a specific message: returns the specified 
   error type*/
int	ft_error(char *msg, char *cmd, int error_type)
{
	if (cmd)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	else
		ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (error_type);
}

/* Changes directory taking as parameter any absolute path,
   checkes if there are permissions to get in the folder and 
   checks if it is a folder and not any other type of file
   return 0 in success and 1 in error  */
int	ft_chdir(char *path)
{
	struct stat	sb;

	if (chdir(path) < 0)
	{
		if (stat(path, &sb) < 0)
			return (ft_error("No such file or directory", path, 1));
		else if (!(sb.st_mode & S_IRUSR))
			return (ft_error("Permission denied", path, 1));
		else if (!(sb.st_mode & S_IFDIR))
			return (ft_error("Not a directory", path, 1));
	}
	return (0);
}

/* Handles how we passed  path argument to the function ft_chdir  and updates 
   t_env struct variables $PWD and $OLDPWD*/
int	ft_go_to(t_env **env, char *path, int cd_type)
{
	char	*old_wd;
	char	*new;
	int		err_type;

	old_wd = getcwd(NULL, 0);
	new = path;
	if (!old_wd || !path)
		err_type = ft_error("No env variable found", NULL, 1);
	ft_update_env(env, ft_strdup("OLDPWD"), ft_strdup(old_wd));
	if (cd_type == CD_PATH_HOME || cd_type == CD_NORMAL)
	{
		if (cd_type == CD_NORMAL)
			new = ft_strjoin(old_wd, new);
		else
			new = ft_strjoin(ft_get_node_value(env, "HOME"), new);
		if (!new || !old_wd)
			return (ft_error("Error joining strings", NULL, 1));
	}
	err_type = ft_chdir(new);
	if (cd_type == CD_OLD)
		printf("%s\n", getcwd(NULL, 0));
	ft_update_env(env, ft_strdup("PWD"), getcwd(NULL, 0));
	free(new);
	return (err_type);
}

/*
   change directory program, handling the following cases:
   1) cd || cd "~" || cd "--"  ---> replasing any of the following
   charancters "~ -- cd" by the environment variable $HOME......................
   2) cd "-" change current directory to the previous one visited, $OLDPWD. Then
   output the path to stdout....................................................
   3) cd "~/" we join the enviroment variable $HOME and the path after the 
   character ~ having at the end a absolute path................................
   4) cd + absolute path, change directory tho any absolute path passed as
   argument
 */
int	ft_cd(char **argv, t_env **env)
{
	if (!argv[1] || !ft_strcmp2(argv[1], "~") || \
			!ft_strcmp2(argv[1], "--"))
		return (ft_go_to(env, ft_strdup(ft_get_node_value(env, "HOME")), \
					CD_NORMAL));
	if (argv[1] && argv[2])
		return (ft_error("cd: too many arguments", NULL, 0));
	if (!ft_strcmp2(argv[1], "-"))
		return (ft_go_to(env, ft_strdup(ft_get_node_value(env, "OLDPWD")), \
					CD_OLD));
	if (!ft_strncmp(argv[1], "~/", ft_strlen(argv[1])))
		return (ft_go_to(env, ft_strdup((argv[1] + 1)), \
					CD_PATH_HOME));
	if (!ft_strncmp(argv[1], "/", ft_strlen(argv[1])))
		return (ft_go_to(env, ft_strdup((argv[1])), \
					CD_NORMAL));
	if (argv[1])
		return (ft_go_to(env, ft_strdup((argv[1])), \
					CD_NORMAL));
	return (0);
}