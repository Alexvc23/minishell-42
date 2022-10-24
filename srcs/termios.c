/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:05:04 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/24 18:30:03 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* 
we set attributes as needed for prompt, echoing passed input,
stablishing cannocal input and enabling sign handling
*/
void	ft_termios(void)
{
	struct termios	attrs;

	int	result[2];
	result[0] = tcgetattr(STDIN_FILENO, &g_vars->term_save);
	result[1] = tcgetattr(STDIN_FILENO, &attrs);
	if (result[0] || result[1])
		perror("tcsetattr\n");
	attrs.c_lflag = (ECHO | ICANON | ISIG);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &attrs))
		perror("tcsetattr\n");
}

/* restablished default termios attributes */
void	reset_terminal(t_shell *t)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t->term_save);
}
