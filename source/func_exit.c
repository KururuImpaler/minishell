/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:57:09 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:20 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		check_val(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && str[i] == '-')
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	numeric(t_cmd *cmd)
{
	ft_putstr_fd("bash: exit: ", 1);
	ft_putstr_fd(cmd->args[1], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	exit(255);
}

void	func_exit_2(t_cmd *cmd, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 1);
		g_shell.ret_val = ft_error(1);
		return ;
	}
	else
		numeric(cmd);
}

void	func_exit(t_cmd *cmd)
{
	int		i;

	if (cmd->ac == 1)
	{
		if (!g_shell.flag)
			ft_putstr_fd("exit\n", 1);
		ft_exit(0);
	}
	i = check_val(cmd->args[1]);
	if (cmd->ac == 2)
	{
		if (i == 1)
		{
			if (!g_shell.flag)
				ft_putstr_fd("exit\n", 1);
			ft_exit(g_shell.error = ft_atoi(cmd->args[1]));
		}
		else
			numeric(cmd);
	}
	if (cmd->ac > 2)
		func_exit_2(cmd, i);
}
