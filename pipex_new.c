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

	cmd = ft_split(argv[i], ' '); /*mettre 2 qund file 1 + voir pour boucle*/
	// if (ft_first_check(cmd) == 0)
	// {
	// 	if (execve(cmd, cmd, NULL) == -1)
	// 	{
	// 		perror("error execve");
	// 		exit(1);
	// 	}
	// 	ft_free_split(cmd);
	// }
	// else
	// {
		path = ft_find_path(env);
		path_cmd = ft_check_cmd(path, cmd);
		path_opt = ft_check_opt(path_cmd, cmd);
		if (execve(path_cmd, path_opt, NULL) == -1)
		{
			perror("error execve");
			exit(1);
		}
		free(path_cmd);
		ft_free_split(path_opt);
	}
// }

void	ft_exe_pipe(int fd_in, int fd_out, char **argv, char **env, int i)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("error dup2 in");
		exit(1);
	}
	close(fd_in);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("error dup2 out");
		exit(1);
	}
	close(fd_out);
	ft_exe(argv, env, i);
}
void	ft_close_and_wait(int *previous_fd, int *fd_pipe0, int *fd_pipe1)
{
	close(*previous_fd);
	*previous_fd = *fd_pipe0;
	close(*fd_pipe1);
	wait(NULL);
}

void	ft_pipe(int argc, char **argv, char **env, int previous_fd)
{
	int		fd_pipe[2];
	int		i;
	pid_t	id;

	i = 1;
	while (++i < argc - 1)
	{
		if (pipe(fd_pipe) == -1)
			return (perror("error pipe"), exit(1));
		id = fork();
		if (id < 0)
			return (perror("error fork"), exit(1));
		if (id == 0)
		{
			if (i == argc - 2)
			{
				fd_pipe[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (fd_pipe[1] == -1)
					return (perror("error opening outfile"), exit(1));
			}
			close(fd_pipe[0]);
			ft_exe_pipe(previous_fd, fd_pipe[1], argv, env, i);
		}
		ft_close_and_wait(&previous_fd, &fd_pipe[0], &fd_pipe[1]);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) env;
	int	previous_fd;

	previous_fd = open(argv[1], O_RDONLY);
	ft_pipe(argc, argv, env, previous_fd);
	return (0);
}

	// char *path[50] = {"/usr/bin/ls", NULL};
	// execve("/usr/bin/ls", path, NULL);