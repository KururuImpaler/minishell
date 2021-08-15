/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_export_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:28 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

void	env_print(t_env *env)
{
	t_env	*cpy;

	cpy = env;
	while (cpy)
	{
		write(1, "declare -x ", 11);
		ft_putstr_fd(cpy->name, 1);
		if (cpy->val)
		{
			write(1, "=\"", 2);
			ft_putstr_fd(cpy->val, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		cpy = cpy->next;
	}
}
