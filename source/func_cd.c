/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:51:44 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:33:02 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

char	*finder(char *str, t_env *env)
{
	t_env	*cpy;
	int		i;

	i = 0;
	cpy = env;
	while (cpy)
	{
		if (ft_strcmp(str, cpy->name) == 0 && (i = 1))
			break ;
		cpy = cpy->next;
	}
	if (i == 1)
		return (cpy->val);
	return ("");
}

void	change_env(t_env *env, char *name, char *val)
{
	t_env	*cpy;
	int		i;

	i = 0;
	cpy = env;
	while (cpy)
	{
		if (ft_strcmp(name, cpy->name) == 0 && (i = 1))
			break ;
		cpy = cpy->next;
	}
	if (i == 1)
		cpy->val = ft_strdup(val);
}

int		check_name(t_env *env, char *name)
{
	t_env *cpy;

	cpy = env;
	while (cpy)
	{
		if (ft_strcmp(name, cpy->name) == 0)
			return (1);
		cpy = cpy->next;
	}
	return (0);
}

void	func_cd_2(DIR *folder, char *path, t_env *env)
{
	char	*pwd;

	g_shell.ret_val = ft_error(0);
	closedir(folder);
	chdir(path);
	if (!(pwd = getcwd(NULL, 0)))
	{
		g_shell.error = 1;
		return ;
	}
	change_env(env, "OLDPWD", finder("PWD", env));
	if (check_name(env, "PWD"))
		change_env(env, "PWD", pwd);
	free(pwd);
}

void	func_cd(t_cmd *cmd, t_env *env, int ac)
{
	DIR		*folder;
	char	*path;

	path = cmd->args[1];
	if (ac == 1)
	{
		if (check_name(env, "HOME"))
			path = finder("HOME", env);
		else
		{
			g_shell.ret_val = ft_error(1);
			ft_putstr_fd("bash: cd: HOME not set\n", 2);
			return ;
		}
	}
	if (!(folder = opendir(path)))
		check_error(cmd->args[1], 2);
	if (folder)
		func_cd_2(folder, path, env);
}
