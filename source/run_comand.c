/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_comand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:25:44 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:34:06 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		syntax_error(t_cmd *cmd, int type)
{
	write(1, "bash: syntax error", 18);
	if (type == 1)
		write(1, ": unexpected end of file\n", 25);
	else
		write(1, " near unexpected token `", 24);
	if (type == 2)
		write(1, &cmd->pipe, 1);
	if (type == 3)
		write(1, "newline", 7);
	if (type == 4)
		write(1, ";;", 2);
	if (type != 1)
		write(1, "'\n", 2);
	return (0);
}

int		error_run(t_cmd *cmd)
{
	int		i;

	test_syntax_2(cmd);
	while (cmd)
	{
		i = 1;
		if (g_shell.syntax_error)
			g_shell.ret_val = ft_error(2);
		else if (!cmd->args[0] && cmd->pipe == '|' && !(--i))
			g_shell.ret_val = ft_error(2);
		else if (!cmd->args[0] && cmd->pipe == ';' && !(--i))
			g_shell.ret_val = ft_error(2);
		else if (cmd->fd && !cmd->file && !(--i))
			g_shell.ret_val = ft_error(2);
		if (g_shell.syntax_error)
			return (syntax_error(cmd, g_shell.syntax_error));
		if (!i && cmd->pipe != ' ')
			return (syntax_error(cmd, 2));
		else if (!i)
			return (syntax_error(cmd, 3));
		cmd = cmd->next;
	}
	return (1);
}

char	**free_envp(char **envp)
{
	if (envp)
		free(envp);
	return (NULL);
}

int		run_commands(void)
{
	t_cmd	*cmd;
	int		error;

	cmd = g_shell.commands;
	while (!g_shell.run && g_shell.exit < 2 && cmd)
	{
		g_shell.flag = 0;
		if (!error_run(cmd))
			return (1);
		if (!cmd->args[0])
		{
			cmd = cmd->next;
			continue ;
		}
		if (!(g_shell.envp = get_env_array(g_shell.env, g_shell.num_env + 1)))
			return (0);
		if (cmd->pipe == '|')
			error = ft_pipe_cmd(&cmd, 0, 0);
		else
			error = ft_next_cmd(&cmd);
		if (error < 0)
			return (0);
		g_shell.envp = free_envp(g_shell.envp);
	}
	return (1);
}
