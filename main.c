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

int	main(int argc, char **argv, char **env)
{
	int	previous_fd;

	if (argc == 5)
	{
		previous_fd = open(argv[1], O_RDONLY);
		if (previous_fd == -1)
		{
			perror(argv[1]);
		}
		ft_pipe(argc, argv, env, previous_fd);
		return (0);
	}
	else
	{
		ft_putstr_fd("Should be : ./pipex file1 cmd1 cmd2 file2", 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
}
