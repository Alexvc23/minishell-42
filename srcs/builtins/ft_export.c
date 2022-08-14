/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:58:13 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/13 16:01:42 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_putenv(t_env **env, char **keys)
{
	char	*value;
	int		i;

	i = -1;
	while (keys[++i])
	{
		value = ft_strdup(ft_get_node_value(env, keys[i]));
		printf("declare -x %s=\"%s\"\n", keys[i], value);
		free(value);
	}
	ft_free((void **) keys);
	return (0);
}

/* 
--> Fetch all env keys and puts in a array
--> Sorts the array alphabetically
--> pass the array to ft_putenv and return success code 0 
*/
static int	ft_sort_env_arr(t_env **env)
{
	char	**keys;
	char	*tmp;
	int		len;
	int		i;
	int		j;

	keys = ft_env_to_key_array(env);
	len = 0;
	while (keys[len])
		len++;
	i = -1;
	while (++i < len - 1)
	{
		j = -1;
		while (++j + i < len)
		{
			if (ft_strncmp(keys[i], keys[i + j], -1) > 0)
			{
				tmp = keys[i];
				keys[i] = keys[i + j];
				keys[i + j] = tmp;
			}
		}
	}
	return (ft_putenv(env, keys));
}

static int	ft_export_err(char *err)
{
	ft_putstr_fd("Invalid key name: '", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("'.\n", STDERR_FILENO);
	return (1);
}

static int	ft_export_one(char *str, t_env **env)
{
	char	*key;
	char	*val;
	int		err;
	int		i;

	key = str;
	err = 0;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i] && !ft_is_valid_key(key))
		return (ft_export_err(key));
	str[i] = '\0';
	val = &str[i + 1];
	if (ft_is_valid_key(key))
		ft_update_env(env, ft_strdup(key), ft_strdup(val));
	else
		err = ft_export_err(key);
	str[i] = '=';
	return (err);
}

int	ft_export(char **argv, t_env **env)
{
	int	status;
	int	i;

	if (!argv[1])
		return (ft_sort_env_arr(env));
	status = 0;
	i = 0;
	while (argv[++i])
		status += ft_export_one(argv[i], env);
	return (status != 0);
}