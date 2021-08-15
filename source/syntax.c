/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:49:07 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:34:25 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

void	ft_save_char(char c)
{
	if (g_shell.stop_run && c != '\n')
		g_shell.c[0] = c;
	else
		g_shell.c[0] = '\0';
}

int		test_syntax(char *s, int j)
{
	int		i;

	if (j < 0)
		j = 0;
	i = j - 1;
	while (s[++i])
	{
		if (!ft_memchr(" \t\v\r\n\f|", s[i], 7))
			return (1);
	}
	return (0);
}

void	test_syntax_2(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd)
	{
		if (i == 0 && cmd->pipe == ';' && cmd->next && cmd->next->pipe == ';')
			i = 1;
		cmd = cmd->next;
	}
	if (!i && g_shell.syntax_error == 4)
		g_shell.syntax_error = 0;
}
