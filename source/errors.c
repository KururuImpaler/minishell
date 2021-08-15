/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:32:52 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		ft_lennbr(int n)
{
	int		len;

	len = 1;
	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_error(int n)
{
	int		len;
	char	*error;

	len = ft_lennbr(n);
	if (len == 1)
		error = g_shell.errors.er1;
	else if (len == 2)
		error = g_shell.errors.er2;
	else
		error = g_shell.errors.er3;
	while (len--)
	{
		error[len] = n % 10 + '0';
		n /= 10;
	}
	return (error);
}
