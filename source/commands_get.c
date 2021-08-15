/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:09:36 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:32:38 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		get_cmd_args(t_list_args *cpy, char **str, int n, int j)
{
	int		pipe;

	cpy = swipe_list(cpy, j);
	if ((j = ft_check_cpy(cpy, &str, n)))
		return (j);
	str[j] = NULL;
	while (cpy && cpy->pipe == ' ')
	{
		str[j + 1] = NULL;
		str[j] = NULL;
		if ((n = get_file_read(cpy, 0)) < 0)
			return (free_arr(str));
		pipe = ' ';
		if (n > 0 && !(cpy = swipe_list(cpy, n)))
			break ;
		if (n > 0)
			continue ;
		if (!(str[j++] = ft_strdup(cpy->arg)))
			return (free_arr(str));
		pipe = cpy->pipe;
		cpy = cpy->next;
	}
	g_shell.arr = str;
	return ((cpy) ? cpy->pipe : pipe);
}

int		get_cmd(t_cmd *cmd, t_list_args *args, int i, int j)
{
	t_list_args	*cpy;
	char		**str;
	int			ac;
	char		pipe;

	cpy = args;
	str = NULL;
	pipe = get_cmd_args(cpy, str, (i - j) + 1, j);
	if (pipe < 0)
		return ((pipe == -2) ? -2 : -1);
	ac = len_arr(g_shell.arr);
	if (!(g_shell.commands = new_command(cmd, g_shell.arr, pipe, ac)))
		return (free_arr(g_shell.arr));
	return (i);
}

int		ft_find_cmd(t_list_args *args, int i)
{
	t_list_args	*cpy;
	int			j;

	cpy = args;
	j = -1;
	while (++j < i)
		cpy = cpy->next;
	while (cpy && cpy->next && cpy->pipe == ' ')
	{
		i++;
		cpy = cpy->next;
	}
	i++;
	return (i);
}

t_cmd	*separator(void)
{
	int			i;
	int			j;

	i = 0;
	while (i >= 0)
	{
		g_shell.file_cmd = NULL;
		g_shell.fd_cmd = 0;
		j = i;
		i = ft_find_cmd(g_shell.args, j);
		if ((i = get_cmd(g_shell.commands, g_shell.args, i, j)) == -2)
			return (free_cmd(g_shell.commands));
	}
	return (g_shell.commands);
}
