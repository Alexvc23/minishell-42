/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:25:13 by fdevigne          #+#    #+#             */
/*   Updated: 2022/07/27 16:20:38 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Simply free the stuff and exit

// This may be leaking as I'm unsure if freeing the global variable will just free everything correctly.
// tcsetattr won't work in the current iteration of this code has I need to input it the termios structure that's generated into ft_termios()
// It doesn't look like this structure is global, so I'm not sure how to do that and I don't want to change your code without talking about it beforhand.

void	ft_exit(int status, t_shell *vars)
{
    //tcsetattr(STDIN_FILENO, TCSAFLUSH, [termios structure]);
    free (vars);
	exit (status);
}