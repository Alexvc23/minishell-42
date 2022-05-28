/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:08:33 by alex-ubun         #+#    #+#             */
/*   Updated: 2021/11/23 11:36:36 by jvalenci         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Écrit la chaine de caractères ’s’ sur le file
   descriptor donné. */

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
	return ;
}
/* 
   int main()
   {
   char buff[100];
   char *test = "tengo la camisa negra";
   int fd;
   int i = 0;

   ft_bzero(buff, (sizeof(buff) / sizeof(buff[0])));
   fd = open("test.txt", O_WRONLY | O_CREAT);
   ft_putstr_fd(test, fd);
   close(fd);
   fd = open("test.txt", O_RDONLY | O_CREAT);
   while (read(fd, &buff[i], 1))
   i++;
   printf("%s\n", buff);
   close(fd);
   }

*/
