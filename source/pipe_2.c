/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:57 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		len_pipe(t_cmd *cmd)
{
	int		pipe;
	int		i;

	i = 0;
	pipe = cmd->pipe;
	while (cmd && pipe == '|')
	{
		++i;
		pipe = cmd->pipe;
		cmd = cmd->next;
	}
	return (i);
}

int		free_pipe(int **fd, pid_t *pid)
{
	int		i;

	i = -1;
	while (fd && fd[++i])
		free(fd[i]);
	if (fd)
		free(fd);
	if (pid)
		free(pid);
	g_shell.pid_fd.fd = NULL;
	g_shell.pid_fd.pid = NULL;
	return (-1);
}

int		pid_null(int *pid, int len)
{
	len--;
	while (pid && len > -1)
	{
		pid[len] = 0;
		len--;
	}
	return (0);
}

int		pipe_null(int **fd, int len)
{
	while (fd && len > -1)
	{
		fd[len] = NULL;
		len--;
	}
	return (0);
}

int		get_pipe(int ***fd, pid_t **pid, t_cmd *cmd)
{
	int		i;
	int		j;

	i = len_pipe(cmd);
	if (!(*fd = (int **)malloc(sizeof(int *) * (i))) || pipe_null(*fd, i - 1))
		return (free_pipe(*fd, *pid));
	if (!(*pid = (pid_t *)malloc(sizeof(pid_t) * (i))) || pid_null(*pid, i))
		return (free_pipe(*fd, *pid));
	j = -1;
	while (++j < i - 1)
	{
		if (!((*fd)[j] = (int *)malloc(sizeof(int) * 2)))
			return (free_pipe(*fd, *pid));
		pipe((*fd)[j]);
	}
	g_shell.pid_fd.fd = *fd;
	g_shell.pid_fd.pid = *pid;
	return (i);
}
