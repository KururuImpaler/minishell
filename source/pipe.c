/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:25:18 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:52 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		fd_file(t_cmd *cmd)
{
	int		fd;
	int		n;
	char	c;

	fd = -1;
	if (cmd->fd == 1)
		fd = open(cmd->file, O_TRUNC | O_WRONLY);
	if (cmd->fd == 2)
		fd = open(cmd->file, O_RDONLY);
	if (cmd->fd == 3)
	{
		fd = open(cmd->file, O_RDWR);
		n = 1;
		while (fd > 0 && n > 0)
			n = read(fd, &c, 1);
		if (fd > 0 && n < 0)
		{
			close(fd);
			return (-1);
		}
	}
	return (fd);
}

int		dup_fd(int ***fd, int j, int i)
{
	if (j == i - 1)
	{
		close((*fd)[j - 1][1]);
		dup2((*fd)[j - 1][0], 0);
	}
	else if (j == 0)
		dup2((*fd)[j][1], 1);
	else
	{
		close((*fd)[j][0]);
		close((*fd)[j - 1][1]);
		dup2((*fd)[j][1], 1);
		dup2((*fd)[j - 1][0], 0);
	}
	return (0);
}

int		close_fd(int ***fd, int j, int i)
{
	if (j == i - 1)
	{
		close((*fd)[j - 1][1]);
		close((*fd)[j - 1][0]);
	}
	else if (j == 0)
		close((*fd)[j][1]);
	else
	{
		close((*fd)[j][1]);
		close((*fd)[j - 1][0]);
	}
	return (0);
}

int		waitpid_fd(pid_t *pid, int i)
{
	int		stat;
	int		j;

	j = -1;
	while (++j < i)
	{
		waitpid(pid[j], &stat, 0);
		errno = WEXITSTATUS(stat);
		g_shell.ret_val = ft_error(errno);
		if (errno < 0)
			return (-1);
	}
	return (0);
}

int		ft_pipe_cmd(t_cmd **cmd, int i, int j)
{
	int		**fd;
	pid_t	*pid;

	g_shell.flag = 1;
	pid = NULL;
	if ((i = get_pipe(&fd, &pid, *cmd)) < 0)
		return (-1);
	j = -1;
	while (++j < i)
	{
		if (!(pid[j] = fork()))
		{
			dup_fd(&fd, j, i);
			errno = ft_next_cmd(cmd);
			if (errno > -1)
				errno = ft_atoi(g_shell.ret_val);
			ft_exit(errno);
		}
		close_fd(&fd, j, i);
		(*cmd) = (*cmd)->next;
	}
	if (waitpid_fd(pid, i))
		return (-1);
	free_pipe(fd, pid);
	return (0);
}
