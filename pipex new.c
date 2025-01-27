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

void	ft_free_split(char **path)
{
	int		i;
	i = 0;

	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free (path);
}

void	ft_exe(char **argv, char **env, int i)
{
	char	**path;
	char	*path_cmd;
	char	**path_opt;
	char	**cmd;

	cmd = ft_split(argv[i + 2], ' '); /*mettre 2 qund file 1 + voir pour boucle*/
	path = ft_find_path(env);
	path_cmd = ft_check_cmd(path, cmd);
	path_opt = ft_check_opt(path_cmd, cmd);
	if (execve(path_cmd, path_opt, NULL) == -1)
	{
		perror("error execve");
		exit(1);
	}
	// voir comment faire pour free car fin du programme
	free(path_cmd);
	ft_free_split(path_opt);
}


void	ft_exe_pipe(int fd_in, int fd_out, char **argv)
{
	
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

void	ft_pipe(int argc, char **argv, char **env)
{
	int		fd_pipe[2];
	int		i;
	pid_t	*id;

	i = 0;
	ft_printf("argc %d", argc);
	while (i < argc - 4)
	{
		if (pipe(fd_pipe[i]) == -1)
		{
			perror("error pipe");
			exit(1);
		}
	i = 0;
	id = NULL;
	while (i < argc - 3)
	{
		id[i] = fork();
		if (id[i] < 0)
		{
			perror("error fork");
			exit(1);
		}
		if (id[0] == 0)
			ft_first_fork(fd_pipe, argv, env);
		else if (id[argc - 4] == 0)
			ft_last_fork(fd_pipe, argv, env, i);
		else
			ft_middle_fork(fd_pipe, argv, env, i);
		waitpid(id[i],NULL, 0);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) env;

	
	ft_pipe(argc, argv, env);
	// ft_exe(argv, env);
	return (0);
}

	// char *path[50] = {"/usr/bin/ls", NULL};
	// execve("/usr/bin/ls", path, NULL);