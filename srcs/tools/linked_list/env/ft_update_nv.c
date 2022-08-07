/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_nv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:04:02 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/07 15:47:18 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* finds the node containing the key str in t_env struct and replace its
   value  */
void	ft_update_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	if (!env || !key || !value)
		return ;
	while (tmp)
	{
		if (!ft_strcmp2(key, tmp->key))
		{
			free(tmp->value);
			free(key);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	tmp = *env;
	ft_add_node_back(&tmp, ft_new_node(key, value));
	return ;
}
