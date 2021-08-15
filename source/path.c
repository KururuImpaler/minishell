/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:49 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		pathcmp2(char *command, char *path)
{
	struct stat		st;
	char			*file;

	if (!(path = ft_strjoin(path, "/")))
		return (-1);
	if (!(file = ft_strjoin(path, command)))
	{
		free(path);
		return (-1);
	}
	free(path);
	if (!stat(file, &st))
	{
		free(file);
		return (1);
	}
	free(file);
	return (0);
}

int		pathcmp1(t_cmd *cmd, char *path)
{
	int		i;
	char	c;
	int		j;
	int		n;

	if (!path)
		return (0);
	i = -1;
	j = 0;
	while (++i > -1)
	{
		n = 0;
		if (ft_memchr(":\0", path[i], 2))
		{
			c = path[i];
			path[i] = '\0';
			n = pathcmp2(cmd->args[0], &path[j]);
			path[i] = c;
			j = i + 1;
		}
		if (path[i] == '\0' || n)
			break ;
	}
	return (n);
}

char	*get_path2(char *command, char *path)
{
	struct stat		st;
	char			*file;

	if (!(path = ft_strjoin(path, "/")))
		return (0);
	if (!(file = ft_strjoin(path, command)))
	{
		free(path);
		return (0);
	}
	free(path);
	if (!stat(file, &st))
		return (file);
	free(file);
	return (command);
}

char	*get_path1(t_cmd *cmd, char *path, int j, int n)
{
	int		i;
	char	c;
	char	*path1;

	if (!path)
		return (0);
	i = -1;
	path1 = "";
	while (++i > -1 && n == 0 && path[i] != '\0')
	{
		n = 0;
		if (ft_memchr(":\0", path[i], 2))
		{
			c = path[i];
			path[i] = '\0';
			if (!(path1 = get_path2(cmd->args[0], &path[j])))
				n = -1;
			path[i] = c;
			j = i + 1;
		}
		if (!n && ft_memcmp(path1, cmd->args[0], ft_strlen(path1)) && ++n)
			free(cmd->args[0]);
	}
	return ((n < 0) ? 0 : path1);
}
