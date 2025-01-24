/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:59:53 by edelanno          #+#    #+#             */
/*   Updated: 2025/01/24 14:59:54 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
// #include <sys/types.h>
#include <sys/wait.h>

size_t	ft_strlenline(const char *s)
{
	size_t	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
			i++;
	}
	return (i);
}

char	*ft_temp(char **newbuffer, char *buffer)
{
	char	*temp;

	temp = ft_strjoinline(*newbuffer, buffer);
	if (temp == NULL)
		return (NULL);
	if (*newbuffer != NULL)
		free(*newbuffer);
	*newbuffer = temp;
	if (*newbuffer == NULL)
		return (NULL);
	return (*newbuffer);
}

char	*ft_read_file(int fd)
{
	int			m;
	char		buffer[BUFFER_SIZE + 1];
	static char	*newbuffer = NULL;

	buffer[0] = '\0';
	m = 1;
	while (m != 0)
	{
		m = read (fd, buffer, BUFFER_SIZE);
		if (m == -1)
		{
			if (newbuffer != NULL)
				free(newbuffer);
			return (NULL);
		}
		buffer[m] = '\0';
		newbuffer = ft_temp(&newbuffer, buffer);
	}
	if (newbuffer == NULL)
		return (NULL);
	return (newbuffer);
}
