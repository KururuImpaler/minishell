/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:42:26 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:34:28 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

void	start_write(int fd)
{
	char	*path;

	if (!(path = find_env(g_shell.env, "PWD\0")))
		path = NULL;
	write(fd, "\x1b[1;36m", ft_strlen("\x1b[1;36m"));
	if (path)
		write(fd, path, ft_strlen(path));
	write(fd, "$", 1);
	write(fd, "\x1b[0m", ft_strlen("\x1b[0m"));
	write(fd, "\x1b[1;36m", ft_strlen("\x1b[1;36m"));
	write(fd, " >> ", ft_strlen(" >> "));
	write(fd, "\x1b[0m", ft_strlen("\x1b[0m"));
	write(fd, "\x1b[36m", ft_strlen("\x1b[36m"));
}

int		end_write(int fd)
{
	write(fd, "\x1b[0m", ft_strlen("\x1b[0m"));
	return (0);
}

void	multiline_write(int fd)
{
	write(fd, "\x1b[0m", ft_strlen("\x1b[0m"));
	write(fd, "\x1b[36m", ft_strlen("\x1b[36m"));
	write(fd, "pipe> ", 6);
	write(fd, "\x1b[0m", ft_strlen("\x1b[0m"));
	write(fd, "\x1b[36m", ft_strlen("\x1b[36m"));
}

int		ft_write_error(int error, t_cmd *cmd)
{
	int		fd;

	fd = g_shell.now_fd[1];
	write(fd, "bash: ", 6);
	if (error == FILENOTFOUND)
	{
		g_shell.ret_val = ft_error(127);
		write(fd, cmd->args[0], ft_strlen(cmd->args[0]));
		write(fd, ": command not found\n", 20);
	}
	if (error == NOFILEORDIR)
	{
		g_shell.ret_val = ft_error(127);
		write(fd, cmd->args[0], ft_strlen(cmd->args[0]));
		write(fd, ": No such file or directory\n", 28);
	}
	return (0);
}
