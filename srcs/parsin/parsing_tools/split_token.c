/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:14:33 by jvalenci          #+#    #+#             */
/*   Updated: 2022/07/07 11:03:55 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_all(char **arr, int i)
{
	while (i > 0)
		free(arr[i--]);
	free(arr);
}

/* 
->	from line 34 to 37 checks if the delimiter meets the conditions to count
	up until current character as a word (of substring)

-> 	line 41 counts characters (increment i++) up until delimiter meets the
	conditions to stop, which are delimiter is properly surrounded by quotes
	and currect character is delimiter and there is something in current string
	index
 */
static int	ft_wordcount(char *s, char c)
{
	int		wc;
	int		i;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] == c) i++;
		if (((s[i] != c && ((ft_var_quotes(s, i, 0) == 0 && (
								s[i] != '"' && s[i] != '\'')) || (ft_var_quotes(
								s, i, 0) == 1 && (
								s[i] == '"' || s[i] == '\''))))) && s[i])
			wc++;
		while ((s[i] != c || ft_var_quotes(s, i, 0) == 1) && s[i])
			i++;
	}
	return (wc);
}

/* 
key algorithim in line 59, while current index is not delimiter or
delimiter is not well quoted continue incrementing i++
*/
static char	*ft_create_word(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && (s[i] != c || ft_var_quotes(s, i, 0) == 1))
		i++;
	str = ft_calloc(i + 1, 1);
	if (!str)
		return (0);
	ft_strlcpy(str, s, i + 1);
	return (str);
}

char	**ft_split_token(char *s, char c)
{
	int		i;
	int		wc;
	char	**arr;

	if (!s)
		return (0);
	wc = ft_wordcount(s, c);
	arr = ft_calloc(wc + 1, sizeof(char *));
	if (!arr)
		return (0);
	i = -1;
	while (++i < wc)
	{
		while (*s == c && ft_var_quotes(s, 0, 0) == 0)
			s++;
		arr[i] = ft_create_word(s, c);
		if (!arr[i])
		{
			ft_free_all(arr, i);
			return (0);
		}
		s = s + ft_strlen(arr[i]);
	}
	arr[i] = 0;
	return (arr);
}