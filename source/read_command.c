/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:29:06 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:34:03 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

char	*free_command(char *command, int error)
{
	g_shell.error = error;
	if (command)
		free(command);
	return (0);
}

t_cmd	*free_command_2(char *command, int error)
{
	free_command(command, error);
	free_args(g_shell.args, NULL);
	return (0);
}

char	*get_command_next(char *command, int i, char *c, int *j)
{
	char	*cpy;

	cpy = command;
	if (!(command = ft_strjoin(command, " ")))
		return (free_command(cpy, 1));
	free(cpy);
	if (*c == '|' && test_syntax(command, *j))
		g_shell.pipes += 1;
	if (*c == ';' && command[i - 1] == ';')
		g_shell.syntax_error = 4;
	if (!ft_memchr(" \t\v\r\n\f|", *c, 7))
		g_shell.pipes = 0;
	command[i] = *c;
	if (*c == '\n' && g_shell.pipes != 1)
		command[i] = '\0';
	else if (*c == '\n' && (*j = i + 1))
		multiline_write(1);
	return (command);
}

char	*stop_read(char *command, int i, int j)
{
	g_shell.exit = 1;
	free(command);
	write(1, " \b\b ", 4);
	if (i == j)
		g_shell.syntax_error = 1;
	if (!(command = ft_strdup("exit")))
		free_command(command, 1);
	return (command);
}

char	*get_command(char *command, int i)
{
	int		n;
	char	c;
	int		j;

	command = ft_strdup(g_shell.c);
	j = -1;
	while (!g_shell.stop_run && command && (n = read(0, &c, 1)) >= 0)
	{
		if (n == 0 && (!ft_strlen(command) || i == j))
			return (stop_read(command, i, j));
		if (n == 0)
		{
			write(1, "  \b\b", 4);
			continue ;
		}
		if (!(command = get_command_next(command, i, &c, &j)))
			return (0);
		if (c == '\n' && g_shell.pipes != 1)
			break ;
		i++;
	}
	ft_save_char(c);
	if (n < 0)
		return (free_command(command, 2));
	return (command);
}
