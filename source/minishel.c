/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:23:40 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:40 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		free_all(char *command, int error)
{
	free_args(g_shell.args, NULL);
	free_cmd(g_shell.commands);
	free_command(command, error);
	return (0);
}

int		ft_commands(void)
{
	int		i;
	char	*command;

	i = (g_shell.c[0] == 0) ? 0 : 1;
	command = zero_2();
	if (!(command = get_command(command, i)))
		return (0);
	if (!(parse_command(command)))
		return (free_all(command, 1));
	if (!g_shell.next_cmd && !(separator()))
		return (free_all(command, 1));
	free(command);
	return (1);
}

int		launch_minishell(void)
{
	g_shell.exit = 0;
	while (g_shell.exit < 2)
	{
		g_shell.run = 1;
		if (!g_shell.c[0])
			start_write(1);
		if (!(ft_commands()))
			return (0);
		end_write(1);
		g_shell.run = g_shell.stop_run;
		g_shell.now_fd[0] = dup(0);
		g_shell.now_fd[1] = dup(1);
		if (!(run_commands()))
			return (0);
		free_all(NULL, 0);
	}
	return (1);
}

int		main(int size, char *arg[], char *envp[])
{
	zero();
	if (!(zero_1()))
		return (free_errors_string());
	g_shell.ret_val = g_shell.errors.er1;
	if (!(g_shell.env = get_env(g_shell.env, envp, -1)))
		ft_exit(1);
	signal(SIGQUIT, sigquit);
	signal(SIGINT, sigint);
	if (!(launch_minishell()))
		ft_exit(g_shell.error);
	(void)size;
	(void)arg;
	ft_exit(0);
}
