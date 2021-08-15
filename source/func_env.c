/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:14 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

void	env_error(t_cmd *cmd)
{
	ft_putstr_fd("env: ", 1);
	ft_putstr_fd(cmd->args[1], 1);
	ft_putstr_fd(": No such file or directory", 1);
	ft_putstr_fd("\n", 1);
}

void	func_env(t_env *env, t_cmd *cmd)
{
	t_env	*cpy;

	cpy = env;
	if (cmd->ac > 1)
	{
		g_shell.ret_val = ft_error(127);
		env_error(cmd);
		return ;
	}
	while (cpy)
	{
		if (cpy->name && cpy->val)
		{
			ft_putstr_fd(cpy->name, 1);
			ft_putstr_fd("=", 1);
			if (cpy->val)
				ft_putstr_fd(cpy->val, 1);
			ft_putstr_fd("\n", 1);
		}
		cpy = cpy->next;
	}
	g_shell.ret_val = ft_error(0);
}
