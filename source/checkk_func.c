/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkk_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:19:40 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:32:25 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		check_func(t_env *env, t_cmd *cmd)
{
	int i;

	i = 0;
	if ((ft_strcmp(cmd->args[0], "cd") == 0) && (i = 1))
		func_cd(cmd, env, cmd->ac);
	else if ((ft_strcmp(cmd->args[0], "pwd") == 0) && (i = 1))
		func_pwd();
	else if ((ft_strcmp(cmd->args[0], "echo") == 0) && (i = 1))
		func_echo(cmd);
	else if ((ft_strcmp(cmd->args[0], "export") == 0) && (i = 1))
		func_export(cmd, env);
	else if ((ft_strcmp(cmd->args[0], "env") == 0) && (i = 1))
		func_env(env, cmd);
	else if ((ft_strcmp(cmd->args[0], "unset") == 0) && (i = 1))
		func_unset(env, cmd);
	else if ((ft_strcmp(cmd->args[0], "exit") == 0) && (i = 1))
		func_exit(cmd);
	return (i);
}
