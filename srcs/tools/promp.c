/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:03:20 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/17 18:19:25 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hide_sig(int sig)
{
	int	fd[2];

	pipe(fd);
	if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	else if (sig == SIGINT)
		write(1, "\n", 1);
	dup2(fd[0], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}
