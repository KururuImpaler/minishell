/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:32:57 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		free_errors_string(void)
{
	if (g_shell.errors.er1)
		free(g_shell.errors.er1);
	if (g_shell.errors.er2)
		free(g_shell.errors.er2);
	if (g_shell.errors.er3)
		free(g_shell.errors.er3);
	return (0);
}

void	ft_exit(int error)
{
	free_env(g_shell.env, NULL, NULL);
	free_all(NULL, 0);
	if (g_shell.envp)
		free(g_shell.envp);
	free_pipe(g_shell.pid_fd.fd, g_shell.pid_fd.pid);
	free_errors_string();
	exit(error);
}
