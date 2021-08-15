/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_ut.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:32:43 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		free_arr(char **arr)
{
	int		i;

	i = -1;
	while (arr && arr[++i])
		free(arr[i]);
	if (arr)
		free(arr);
	return (-2);
}

int		ft_check_cpy(t_list_args *cpy, char ***str, int n)
{
	int		i;

	i = (!cpy) ? -1 : -2;
	if (!cpy || (cpy && !((*str) = (char **)malloc(sizeof(char *) * n))))
		return (i);
	return (0);
}
