/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:04:57 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/08 17:02:22 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* populates t_env structure with env variables taken from parent process */
t_env	*ft_set_env(char **argv)
{
	t_env	*tmp;
	char	**args;
	int		i;

	i = -1;
	args = NULL;
	while (argv[++i])
	{
		args = ft_split(argv[i], '=');
		if (!args)
			return (NULL);
		if (args[1])
			ft_add_node_back(&tmp, ft_new_node(ft_strdup(args[0]), \
						ft_strdup(args[1])));
		else
			ft_add_node_back(&tmp, ft_new_node(ft_strdup(args[0]), \
						ft_strdup("")));
	}
	ft_free((void **)args);
	return (tmp);
}
