/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:59:55 by edelanno          #+#    #+#             */
/*   Updated: 2025/01/27 09:59:56 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include "printf/ft_printf.h"

// int	ft_first_check(char **cmd)
// {
// 	if(ft_strchr(cmd, '/') != NULL)
// 	{
// 		if(access(cmd, X_OK) != 0)
// 			return (-1);
// 	}

// 	return (0);
// }

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
