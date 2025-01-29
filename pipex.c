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

void	ft_exe(char *argv, char **env)
{
	char	**path;
	char	*path_cmd;
	char	**path_opt;
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (ft_first_check(&cmd[0]) == 0)
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			return (perror("error first check cmd"), exit (1));
		ft_free_split(cmd);
	}
	else
	{
		path = ft_find_path(env);
		path_cmd = ft_check_cmd(path, cmd);
		path_opt = ft_check_opt(path_cmd, cmd);
		if (execve(path_cmd, path_opt, NULL) == -1)
		{
			free(path_cmd);
			ft_free_split(path_opt);
			return (perror("error execve"), exit (1));
		}
	}
}

void	ft_exe_pipe(int fd_in, int fd_out, char *argv, char **env)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (perror("error dup2 in"), exit(1));
	close(fd_in);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (perror("error dup2 out"), exit(1));
	close(fd_out);
	ft_exe(argv, env);
}

void	ft_close_and_wait(int *previous_fd, int *fd_pipe0, int *fd_pipe1)
{
	close(*previous_fd);
	*previous_fd = *fd_pipe0;
	close(*fd_pipe1);
	wait(NULL);
}

int	ft_outfile(char **argv, int argc)
{
	int	fd_out;

	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == - 1)
		return (perror("error opening outfile"), exit(1), -1);
	return (fd_out);
}

void	ft_pipe(int ac, char **av, char **env, int previous_fd)
{
	int		fdpip[2];
	int		i;
	pid_t	id;

	i = 1;
	while (++i < ac - 1)
	{
		if (pipe(fdpip) == -1)
			return (perror("error pipe"), exit(1));
		if (previous_fd != -1)
			id = fork();
		if (previous_fd != -1 && id < 0)
			return (perror("error fork"), exit(1));
		if (previous_fd != -1 && id == 0)
		{
			if (i == ac - 2)
				fdpip[1] = ft_outfile(av, ac);
			close(fdpip[0]);
			ft_exe_pipe(previous_fd, fdpip[1], av[i], env);
		}
		ft_close_and_wait(&previous_fd, &fdpip[0], &fdpip[1]);
	}
}
