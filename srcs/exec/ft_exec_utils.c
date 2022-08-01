/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:50:44 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/01 12:45:23 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_cmd *cmd)
{
	if (cmd->argv[0][0] == 1)
		return (1);
	if (ft_strncmp(cmd->argv[0], "echo", ft_strlen(cmd->argv[0])))
		return (1);
	if (ft_strncmp(cmd->argv[0], "export", ft_strlen(cmd->argv[0])))
		return (1);
	if (ft_strncmp(cmd->argv[0], "unset", ft_strlen(cmd->argv[0])))
		return (1);
	if (ft_strncmp(cmd->argv[0], "env", ft_strlen(cmd->argv[0])))
		return (1);
	if (ft_strncmp(cmd->argv[0], "pwd", ft_strlen(cmd->argv[0])))
		return (1);
	if (ft_strncmp(cmd->argv[0], "cd", ft_strlen(cmd->argv[0])))
		return (1);
	if (ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0])))
		return (1);
	return (0);
}

