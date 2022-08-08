/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 08:03:56 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/08 13:27:15 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		ft_free((void **)tmp->argv);
		if (tmp->in)
			free(tmp->in);
		if (tmp->out)
			free(tmp->out);
		free(tmp);
	}
}
