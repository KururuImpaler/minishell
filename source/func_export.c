/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:41:22 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:24 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		export_error(t_cmd *cmd, int fl, int i)
{
	g_shell.ret_val = ft_error(1);
	if (fl == 1)
	{
		write(1, "bash: export: `", 15);
		ft_putstr_fd(cmd->args[i], 1);
		write(1, "': not a valid identifier\n", 27);
	}
	return (0);
}

int		change_env_exp(t_env *env, char *name, char *data, int i)
{
	t_env	*cpy;

	cpy = env;
	while (cpy)
	{
		if (ft_strcmp(name, cpy->name) == 0)
		{
			free(cpy->data);
			cpy->data = data;
			cpy->val = &cpy->data[i + 1];
			return (1);
		}
		cpy = cpy->next;
	}
	return (0);
}

void	get_name_val(t_env *env, char *str)
{
	int		i;
	char	*name;
	char	*val;
	char	*data;

	i = 0;
	name = NULL;
	val = NULL;
	data = NULL;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (!(name = ft_substr(str, 0, i)))
	{
		g_shell.error = 1;
		return ;
	}
	data = str;
	if (str[i] == '=')
		val = &data[i + 1];
	if (change_env_exp(env, name, str, i) == 0)
		new_env(env, name, data, val);
}

int		export_one(t_cmd *cmd, t_env *env, int i)
{
	int		c;
	int		fl;
	int		fl2;
	char	*str;

	fl = 0;
	fl2 = 0;
	c = -1;
	g_shell.ret_val = ft_error(0);
	while (cmd->args[i][++c] != '\0' && fl2 != 1)
	{
		if (ft_isalnum(cmd->args[i][c]) == 0 || cmd->args[i][0] == '=')
			fl = 1;
		if (cmd->args[i][c] == '=' && (fl2 = 1) && fl == 1)
			return (export_error(cmd, 1, i));
	}
	if (!(str = ft_strdup(cmd->args[i])))
		return (0);
	if (fl == 0)
		get_name_val(env, str);
	return (0);
}

void	func_export(t_cmd *cmd, t_env *env)
{
	int		i;

	i = 0;
	if (cmd->ac == 1)
		env_print(env);
	else
		while (++i < cmd->ac)
			export_one(cmd, env, i);
}
