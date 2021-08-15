/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:10 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		check_flag(t_cmd *cmd, int i)
{
	int n;

	n = 1;
	if (cmd->args[i][0] != '-' || cmd->args[i][1] != 'n')
		return (0);
	while (cmd->args[i][++n] != '\0')
		if (cmd->args[i][n] != 'n')
			return (0);
	return (1);
}

void	func_echo(t_cmd *cmd)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	if (cmd->ac == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	while (check_flag(cmd, i) && (flag = 1))
		i++;
	i -= 1;
	while (++i < cmd->ac)
	{
		if (ft_strcmp(cmd->args[i], "$?") == 0)
			ft_putstr_fd(g_shell.ret_val, 1);
		else
			ft_putstr_fd(cmd->args[i], 1);
		if (i + 1 < cmd->ac)
			write(1, " ", 1);
	}
	if (flag != 1)
		write(1, "\n", 1);
	g_shell.ret_val = ft_error(0);
}
