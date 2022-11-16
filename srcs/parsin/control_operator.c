/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:59:38 by jvalenci          #+#    #+#             */
/*   Updated: 2022/11/16 19:09:11 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
    Scan line passed searching for redirections and cmd arguments, then
    fils t_cmd structure to use it in execution
->	cmd_true will store entire line, being used by functions
	ft_redirec_input (search input files or heredoc), by ft_with_var
	(to expand variable if any ) and ft_redirection_output to extract
	redirection outfile information
->  args by the other side is the result of cmd_true already treated in the
    previous step, ready to be passed in ft_gro_redir(get rid of redirections)
    storing in args only arguments that will be executed
*/
void	ft_fill_cmd(char *cmd_b, t_cmd *cmd)
{
	char	*cmd_true;
	char	*args;
	char	*temp;
	int		err[2];

	args = 0;
	temp = ft_skip_spaces(ft_strdup(cmd_b));
	free(cmd_b);
	cmd_true = ft_with_var(temp, NULL, NULL, 0);
	err[0] = ft_redirec_input(cmd_true, cmd, temp, 0);
	err[1] = ft_redirec_output(cmd_true, cmd, NULL, 0);
	if ((err[0] == -1 || err[1] == -1))
	{
		ft_fill_err(cmd);
		ft_free_multiple(cmd_true, temp, NULL, NULL);
		return ;
	}
	args = ft_conv_redir(cmd_true);
	args = ft_skip_spaces(args);
	cmd->argv = ft_conv_args(args);
	cmd->argv[0] = ft_get_first(args);
	without_quote_args(cmd);
	ft_free_multiple(args, cmd_true, temp, NULL);
	cmd->next = NULL;
}

/* 
-> split line with arguments into tokens
-> instancites t_cmd structure
-> fill up t_cmd structure with arguments
-> allocate memory for next token if any
-> check erros 
*/
void	ft_create_tokens(char *cmd_b, t_cmd *cmd)
{
	char	**b_sep;
	int		i;

	b_sep = ft_split_token(cmd_b, '|');
	i = 0;
	if (!b_sep[i])
	{
		ft_inicialize_cmd(cmd);
		cmd->argv = malloc(1);
		cmd->argv = NULL;
	}
	while (b_sep[i])
	{
		ft_fill_cmd(b_sep[i], cmd);
		if (b_sep[i + 1])
		{
			cmd->next = malloc(sizeof(t_cmd));
			if (!cmd->next)
				return ;
			ft_inicialize_cmd(cmd->next);
		}
		cmd = cmd->next;
		i++;
	}
	free(b_sep);
}
