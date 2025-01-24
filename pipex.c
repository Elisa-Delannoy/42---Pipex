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
#include <fcntl.h>
// #include <sys/types.h>
#include <sys/wait.h>

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

char	**ft_find_path(char **env)
{
	char	**chk_path;
	char	**path;
	int		i;
	
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	chk_path = ft_split(env[i], ':');
	path = ft_calloc(i, sizeof(char **));
	i = 0;
	while (chk_path[i])
	{
		path[i] = ft_strjoin(chk_path[i], "/");
		free (chk_path[i]);
		i++;
	}
	free (chk_path);
	return (path);
}	

char	*ft_check_cmd(char **path, char **cmd)
{
	char	*path_cmd;
	int		j;

	j = 0;
	path_cmd = ft_strjoin(path[j], cmd[0]);
	while (path[j] && access(path_cmd, X_OK) != 0)
	{
		free(path_cmd);
		j++;
		path_cmd = ft_strjoin(path[j], cmd[0]);
	}
	ft_free_split(path);
	if (access(path_cmd, X_OK) != 0)
		return ("error cmd"); /*to modify*/
	return(path_cmd);
}

char	**ft_check_opt(char *path_cmd, char **cmd)
{
	free (cmd[0]);
	cmd[0] = ft_strdup(path_cmd);
	return(cmd);
}

void	ft_exe(char **argv, char **env)
{
	char	**path;
	char	*path_cmd;
	char	**path_opt;
	char	**cmd;	

	cmd = ft_split(argv[2], ' '); /*mettre 2 qund file 1 + voir pour boucle*/
	path = ft_find_path(env);
	path_cmd = ft_check_cmd(path, cmd);
	path_opt = ft_check_opt(path_cmd, cmd);
	// printf("path_cmd =%s\n", path_cmd);
	// int i = -1;
	// while (path_opt[++i])
	// 	printf("path_opt =%s\n", path_opt[i]);
	if (execve(path_cmd, path_opt, NULL) == -1)
	{
		perror("error execve");
		exit(1);
	}
	// voir comment faire pour free car fin du programme
	free(path_cmd);
	ft_free_split(path_opt);
}

void	ft_outfile(int *fd_pipe, char **argv)
{
	int	fd_file2;

	fd_file2 = open(argv[3], O_WRONLY); /*mettre 4 quand 2 commande puis voir pour plus*/
	if (fd_file2 == -1)
	{
		perror("error opening outfile");
		exit(1);
	}
	fd_pipe[1] = fd_file2;
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_file2);
	// close(fd_pipe[1]);
}

void	ft_pipe(int fd_file, char **argv, char **env)
{
	int	fd_pipe[2];
	int	id;

	if (pipe(fd_pipe) == -1)
	{
		perror("error pipe");
		exit(1);
	}
	id = fork();
	if (id < 0)
	{
		perror("error fork");
		exit(1);
	}
	if (id == 0)
	{
		close (fd_pipe[1]);
		fd_pipe[0] = fd_file;
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_file);
		close(fd_pipe[0]);
		ft_exe(argv, env);
	}
	else
	{
		close(fd_pipe[0]);
		ft_outfile(fd_pipe, argv);
		close(fd_pipe[1]);
		printf("after outfile\n");
		// wait(NULL);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		fd_file;
	(void) argc;
	(void) env;

	fd_file = open(argv[1], O_RDONLY);
	if (fd_file == -1)
	{
		perror("error opening infile");
		exit(1);
	}
	ft_pipe(fd_file, argv, env);
	// ft_exe(argv, env);
	return (0);
}

	// char *path[50] = {"/usr/bin/ls", NULL};
	// execve("/usr/bin/ls", path, NULL);