/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:22:43 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:34:15 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

void	sigint(int n)
{
	g_shell.signal = 1;
	(void)n;
	if (g_shell.run)
	{
		write(STDOUT_FILENO, " \b\b \b\b \b\n", 9);
		g_shell.stop_run = 1;
	}
	else
		write(1, "\n", 1);
	g_shell.ret_val = ft_error(130);
	start_write(1);
}

void	sigquit(int n)
{
	g_shell.signal = 1;
	(void)n;
	if (!g_shell.run)
	{
		write(1, "Quit: 3\n", 8);
		g_shell.ret_val = ft_error(131);
	}
	else
		write(STDOUT_FILENO, " \b\b \b\b \b", 8);
}
