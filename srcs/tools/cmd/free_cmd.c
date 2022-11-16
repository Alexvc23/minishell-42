/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 08:03:56 by jvalenci          #+#    #+#             */
/*   Updated: 2022/11/16 18:39:11 by alexanderva      ###   ########.fr       */
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
		if (tmp->heredoc_in)
			free(tmp->heredoc_in);
		free(tmp);
	}
}
