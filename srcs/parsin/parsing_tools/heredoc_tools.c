/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:53:12 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/17 18:24:30 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*inicialize_heredoc(void)
{
	t_heredoc	*temp;

	temp = malloc(sizeof(t_heredoc));
	if (!temp)
		return (NULL);
	temp->path = NULL;
	temp->i = -1;
	temp->heredoc = NULL;
	temp->temp = NULL;
	temp->is_open = -1;
	return (temp);
}
