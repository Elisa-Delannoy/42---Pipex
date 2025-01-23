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
	// int		i;
	// char	**opt;

	// i = 1;
	// if (!cmd[1])
	// {
	// 	ft_free_split(cmd);
	// 	return (path_cmd);
	// }
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

	cmd = ft_split(argv[1], ' '); /*mettre 2 qund file 1 + voir pour boucle*/
	path = ft_find_path(env);
	path_cmd = ft_check_cmd(path, cmd);
	path_opt = ft_check_opt(path_cmd, cmd);
	execve(path_cmd, path_opt, NULL);
	free(path_cmd);
	ft_free_split(path_opt);
}


int	main(int argc, char **argv, char **env)
{
	(void)	argc;
	
	ft_exe(argv, env);

	return (0);
}

	// char *path[50] = {"/usr/bin/ls", NULL};
	// execve("/usr/bin/ls", path, NULL);