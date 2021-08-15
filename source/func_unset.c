/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:36 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

t_env	*delete_next_env(t_env *env1, char *name)
{
	t_env	*cpy;

	cpy = NULL;
	if (!ft_strncmp(env1->next->name, name, ft_strlen(name) + 1))
	{
		cpy = env1->next;
		env1->next = env1->next->next;
		if (cpy->name)
			free(cpy->name);
		if (cpy->data)
			free(cpy->data);
		free(cpy);
	}
	return (env1);
}

t_env	*delete_env(t_env *env, char *name)
{
	t_env	*env1;

	env1 = env;
	while (env1)
	{
		if (env1->name && !ft_strncmp(env1->name, name, ft_strlen(name) + 1))
		{
			g_shell.env = env1->next;
			if (env1->name)
				free(env1->name);
			if (env1->data)
				free(env1->data);
			free(env1);
			return (g_shell.env);
		}
		if (env1->next && env1->next->name && name)
			env1 = delete_next_env(env1, name);
		env1 = env1->next;
	}
	return (env);
}

void	func_unset(t_env *env, t_cmd *cmd)
{
	int i;

	i = 0;
	g_shell.ret_val = ft_error(0);
	while (++i < cmd->ac)
	{
		delete_env(env, cmd->args[i]);
	}
}
