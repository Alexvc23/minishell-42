/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandervalencia <alexandervalencia@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:13:15 by alexanderva       #+#    #+#             */
/*   Updated: 2022/11/15 09:21:30 by alexanderva      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char * get_file_text(int fd) 
{
    char *result;
    char *temp;
    char *str;

    result = NULL;
    str = get_next_line(fd);
    while (str)
    {
        if (!result)
            result = ft_strdup("");
        temp = ft_strjoin(result, str);
        free(result);
        result = ft_strdup(temp); 
        free(temp);
        free(str);
        str = get_next_line(fd);
    }
    return (result);
}
