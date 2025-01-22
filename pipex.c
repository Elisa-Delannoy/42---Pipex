/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:47:47 by edelanno          #+#    #+#             */
/*   Updated: 2025/01/21 15:47:49 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <stdio.h>
#include <time.h>
// #include <sys/types.h>
#include <sys/wait.h>

int	ft_find_path(char **env)
{
	int	i;
	
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	return (i);
}

void	ft_check_cmd(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(env[ft_find_path(env)], ':');
}

int	main(int argc, char **argv, char **env)
{
	// int	id;
	(void)	argc;
	(void)	argv;

	ft_check_cmd(env);


	// , et dans path faire un split pour parcourir tous les elements du tableaux jusque trouver la commande puis ensuite executer avec execve
	return (0);
}

// int main()
// {
// 	int id;

// 	id = fork();
// 	printf("hello wolrd %d\n", id);
// 	return (0);
// }