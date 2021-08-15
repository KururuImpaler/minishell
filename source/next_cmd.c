/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:23:04 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:43 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		ft_args_hand(t_cmd *cmd, char *path, int i)
{
	while (cmd->args[++i])
	{
		path = cmd->args[i];
		if (!(cmd->args[i] = ft_subarg(path, ft_strlen(path), 0, 0)))
		{
			cmd->args[i] = path;
			return (-1);
		}
		free(path);
	}
	if (cmd->file)
	{
		path = cmd->file;
		if (!(cmd->file = ft_subarg(path, ft_strlen(path), 0, 0)))
		{
			cmd->file = path;
			return (-1);
		}
		free(path);
	}
	return (0);
}

int		check_path(t_cmd *cmd, t_env *env)
{
	char		*path;
	int			i;
	struct stat	st;

	if (ft_args_hand(cmd, NULL, -1) < 0)
		return (-1);
	if (check_func(g_shell.env, cmd))
		return (2);
	if (!ft_memchr("./", cmd->args[0][0], 2))
	{
		if (!find_env(env, "PATH\0"))
			return (3);
		i = pathcmp1(cmd, find_env(g_shell.env, "PATH\0"));
		if (i <= 0)
			return (i);
		if (!(path = get_path1(cmd, find_env(g_shell.env, "PATH\0"), 0, 0)))
			return (-1);
		cmd->args[0] = path;
	}
	else if (lstat(cmd->args[0], &st))
		return (3);
	return (1);
}

int		ft_run_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		i;

	g_shell.signal = 0;
	if ((i = check_path(cmd, g_shell.env)) == 0 || i == 3)
	{
		ft_write_error(FILENOTFOUND + i, cmd);
		return (1);
	}
	if (i < 0 || i == 2)
		return (i);
	pid = fork();
	if (!pid)
	{
		errno = execve(cmd->args[0], cmd->args, g_shell.envp);
		if (errno > -1)
			errno = ft_atoi(g_shell.ret_val);
		ft_exit(errno);
	}
	else
		waitpid(pid, &i, 0);
	errno = WEXITSTATUS(i);
	if (errno < 0 || !g_shell.signal)
		g_shell.ret_val = ft_error(errno);
	return (0);
}

int		ft_file_cmd(t_cmd *cmd, int fd, pid_t pid, int stat)
{
	fd = fd_file(cmd);
	if (fd < 0)
	{
		g_shell.error = 2;
		return (0);
	}
	pid = fork();
	if (!pid)
	{
		if (cmd->fd == 2)
			dup2(fd, 0);
		else
			dup2(fd, 1);
		errno = ft_run_cmd(cmd);
		if (errno > -1)
			errno = ft_atoi(g_shell.ret_val);
		ft_exit(errno);
	}
	else
		waitpid(pid, &stat, 0);
	close(fd);
	errno = WEXITSTATUS(stat);
	if (errno > -1)
		g_shell.ret_val = ft_error(errno);
	return ((errno < 0 || g_shell.flag) ? errno : 1);
}

int		ft_next_cmd(t_cmd **cmd)
{
	int		error;

	if ((*cmd)->fd && (*cmd)->args[0] && ft_memcmp("exit", (*cmd)->args[0], 5))
		error = ft_file_cmd(*cmd, 0, 0, 0);
	else
		error = ft_run_cmd(*cmd);
	if (error > -1)
		(*cmd) = (*cmd)->next;
	return (error);
}
