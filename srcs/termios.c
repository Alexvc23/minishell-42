/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:05:04 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/08 17:42:51 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* 
we set attributes as needed for prompt, echoing passed input,
stablishing cannocal input and enabling sign handling
*/

void	ft_termios(void)
{
	int result[2];
	result[0] = tcgetattr(0, &g_vars->term_save);
	result[1] = tcgetattr(0, &g_vars->term_new);
	if (result[0] || result[1])
		perror("tcsetattr\n");
	g_vars->term_new.c_lflag = (ECHO | ICANON | ISIG);
	if (tcsetattr(0, 0, &g_vars->term_new))
		perror("tcsetattr\n");
}

/* restablished default termios attributes */
void	reset_terminal(t_shell *t)
{
	tcsetattr(0, 0, &t->term_save);
}
