/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:46 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int			free_args(t_list_args *args, t_list_args *list)
{
	t_list_args	*cpy;

	if (list)
		free(list);
	while (args)
	{
		if (args->arg)
			free(args->arg);
		cpy = args;
		args = args->next;
		free(cpy);
	}
	return (0);
}

t_list_args	*swipe_list(t_list_args *list, int i)
{
	while (i-- > 0 && list)
		list = list->next;
	return (list);
}

int			new_arg(char *arg, int i, int j, char pipe)
{
	t_list_args	*list;
	t_list_args	*cpy;

	if (!(list = (t_list_args *)malloc(sizeof(t_list_args))))
		return (free_args(g_shell.args, NULL));
	list->arg = NULL;
	if (arg && !(list->arg = ft_substr(arg, i, j - i)))
		return (free_args(g_shell.args, list));
	list->quotes = g_shell.quotes;
	list->pipe = pipe;
	list->next = NULL;
	if (g_shell.args == NULL)
	{
		g_shell.args = list;
		return (1);
	}
	cpy = g_shell.args;
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = list;
	return (1);
}

int			parse_command(char *command)
{
	int		i;
	int		j;

	i = 0;
	while (command[i] != '\0')
	{
		g_shell.quotes = 0;
		i = skip_space(command, i);
		j = skip_to_space(command, i);
		if (j == i && ft_memchr("|;", command[i], 2))
		{
			if (!(new_arg(NULL, i, j, command[i])))
				return (0);
			j++;
		}
		else if (i != j && !(new_arg(command, i, j, ' ')))
			return (0);
		i = j;
		i = skip_space(command, i);
	}
	if (i == 0)
		g_shell.next_cmd = 1;
	return (1);
}
