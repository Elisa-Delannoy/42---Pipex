/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:04:20 by edelanno          #+#    #+#             */
/*   Updated: 2025/01/21 17:04:21 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define	PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

# if BUFFER_SIZE > 1000000
#  undef BUFFER_SIZE 
#  define BUFFER_SIZE 1000000
# endif

// # include "libft/libft.h"
// # include "printf/ft_printf.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

char	*ft_read_file(int fd);
char	*ft_strjoinline(char const *s1, char const *s2);
char	*ft_strchrline(const char *s, int c);
char	*ft_strdupline(const char *s);
void	*ft_callocline(size_t nmemb, size_t size);
size_t	ft_strlenline(const char *s);


#endif
