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
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <time.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "libft/libft.h"

char	**ft_find_path(char **env);
char	*ft_check_cmd(char **path, char **cmd);
char	**ft_check_opt(char *path_cmd, char **cmd);
void	ft_free_split(char **path);
int		ft_first_check(char **cmd);
void	ft_pipe(int ac, char **av, char **env, int previous_fd);

#endif
