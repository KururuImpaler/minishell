/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:32 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

void	func_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putstr_fd(path, 1);
	free(path);
	ft_putstr_fd("\n", 1);
	g_shell.ret_val = ft_error(0);
}
