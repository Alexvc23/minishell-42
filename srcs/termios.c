/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:05:04 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/08 06:04:52 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* 
we set attributes as needed for prompt, echoing passed input,
stablishing cannocal input and enabling sign handling
*/

void ft_termios(void)
{
	struct termios termios_new;

	if (tcgetattr(0, &g_vars->term_save))
		perror("tcgetattr\n");
	termios_new = g_vars->term_save;
	termios_new.c_lflag = (ECHO | ICANON | ISIG);
	if (tcsetattr(0, 0, &termios_new))
		perror("tcsetattr\n");
}

/* restablished default termios attributes */
void	reset_terminal(t_shell *t)
{
	tcsetattr(0, 0, &t->term_save);
}