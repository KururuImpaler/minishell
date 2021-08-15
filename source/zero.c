/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:07:24 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:34:32 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

void	zero(void)
{
	g_shell.env = NULL;
	g_shell.bin_path = NULL;
	g_shell.envp = NULL;
	g_shell.num_env = 0;
	g_shell.error = 0;
	g_shell.envp = NULL;
	g_shell.c[0] = '\0';
	g_shell.c[1] = '\0';
}

int		free_errors(void)
{
	if (g_shell.errors.er1)
		free(g_shell.errors.er1);
	if (g_shell.errors.er2)
		free(g_shell.errors.er2);
	if (g_shell.errors.er3)
		free(g_shell.errors.er3);
	return (0);
}

int		zero_1(void)
{
	g_shell.errors.er1 = NULL;
	g_shell.errors.er2 = NULL;
	g_shell.errors.er3 = NULL;
	if (!(g_shell.errors.er1 = ft_strdup("0")))
		return (0);
	if (!(g_shell.errors.er2 = ft_strdup("00")))
		return (0);
	if (!(g_shell.errors.er3 = ft_strdup("000")))
		return (0);
	return (1);
}

char	*zero_2(void)
{
	g_shell.stop_run = 0;
	g_shell.args = NULL;
	g_shell.commands = NULL;
	g_shell.pipes = 0;
	g_shell.next_cmd = 0;
	g_shell.syntax_error = 0;
	return (0);
}
