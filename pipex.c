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

void	ft_first_fork(int **fd_pipe, char **argv, char **env)
{
	int	fd_file;

	fd_file = open(argv[1], O_RDONLY);
	if (fd_file == -1)
	{
		perror("error opening infile");
		exit(1);
	}
	dup2(fd_file, STDIN_FILENO);
	dup2(fd_pipe[0][1], STDOUT_FILENO);
	close(fd_file);
	close(fd_pipe[0][1]);
	ft_exe(argv, env, 0);
}

void	ft_last_fork(int **fd_pipe, char **argv, char **env, int i)
{
	int	fd_file2;

	fd_file2 = open(argv[i + 3], O_WRONLY); /*mettre 4 quand 2 commande puis voir pour plus*/
	if (fd_file2 == -1)
	{
		perror("error opening outfile");
		exit(1);
	}
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_file2, STDOUT_FILENO);
	close(fd_file2);
	close(fd_pipe[0]);
	ft_exe(argv, env, i);
}

void	ft_middle_fork(int **fd_pipe, char **argv, char **env, int i)
{
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	ft_exe(argv, env, i);
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