/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:05:40 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:32:33 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int			len_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int			get_file_read(t_list_args *list, int fd)
{
	if (ft_memcmp(">\0", list->arg, 2) && ft_memcmp("<\0", list->arg, 2) &&
	ft_memcmp(">>\0", list->arg, 3))
		return (0);
	if (list->quotes)
		return (0);
	if (g_shell.file_cmd)
		free(g_shell.file_cmd);
	g_shell.file_cmd = NULL;
	g_shell.fd_cmd = 0;
	if (list->next && list->next->arg)
		if (!(g_shell.file_cmd = ft_strdup(list->next->arg)))
			return (-1);
	if (!ft_memcmp(">\0", list->arg, 2))
		g_shell.fd_cmd = 1;
	if (!ft_memcmp("<\0", list->arg, 2))
		g_shell.fd_cmd = 2;
	if (!ft_memcmp(">>\0", list->arg, 3))
		g_shell.fd_cmd = 3;
	if (g_shell.file_cmd)
	{
		fd = open(g_shell.file_cmd, O_RDWR | O_CREAT, 00600 | 00060 | 00006);
		if (fd > 0)
			close(fd);
	}
	return (2);
}

t_cmd		*free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*cpy;

	while (cmd)
	{
		i = -1;
		while (cmd->args && cmd->args[++i])
			free(cmd->args[i]);
		if (cmd->args)
			free(cmd->args);
		if (cmd->file)
			free(cmd->file);
		cpy = cmd;
		cmd = cmd->next;
		free(cpy);
	}
	return (0);
}

t_cmd		*new_command(t_cmd *cmd, char **arg, char pipe, int ac)
{
	t_cmd	*cpy;
	t_cmd	*list;

	if (!(list = (t_cmd *)malloc(sizeof(t_cmd))))
		return (free_cmd(g_shell.commands));
	list->args = arg;
	list->ac = ac;
	list->pipe = pipe;
	list->file = g_shell.file_cmd;
	list->fd = g_shell.fd_cmd;
	list->next = NULL;
	if (!cmd)
		return (list);
	cpy = cmd;
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = list;
	return (cmd);
}
