/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:25:13 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/09 14:30:56by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_exit(t_cmd *cmd)
{
    ft_free_cmd(cmd);
    free(g_vars->pids);
    reset_terminal(g_vars);
    ft_free_env(g_vars->env);
    free(g_vars);
    ft_putstr_fd("exit\n", 1 );
    exit(g_vars->status);
}
