/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:32:47 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

t_env	*new_env(t_env *env, char *name, char *data, char *val)
{
	t_env	*cpy;
	t_env	*list;

	if (!(list = (t_env *)malloc(sizeof(t_env))))
		return (0);
	list->name = name;
	list->data = data;
	list->val = val;
	list->next = NULL;
	g_shell.num_env += 1;
	if (env == NULL)
		return (list);
	cpy = env;
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = list;
	return (env);
}

t_env	*free_env(t_env *env, char *name, char *data)
{
	t_env	*cpy;

	if (name)
		free(name);
	if (data)
		free(data);
	while (env)
	{
		if (env->name)
			free(env->name);
		if (env->data)
			free(env->data);
		cpy = env;
		env = env->next;
		free(cpy);
	}
	return (0);
}

t_env	*get_env(t_env *env, char **envp, int n)
{
	char	*name;
	char	*data;
	int		j;

	while (envp[++n])
	{
		j = 0;
		while (envp[n][j] != '=')
			j++;
		if (!(name = ft_substr(envp[n], 0, j)))
			return (free_env(env, NULL, NULL));
		if (!(data = ft_strdup(envp[n])))
			return (free_env(env, name, NULL));
		if (!(env = new_env(env, name, data, &data[j + 1])))
			return (free_env(env, name, data));
	}
	return (env);
}

char	*find_env(t_env *env, char *name)
{
	t_env	*cpy;
	int		len;

	len = ft_strlen(name) + 1;
	cpy = env;
	while (cpy)
	{
		if (!ft_memcmp(name, cpy->name, len))
			return (cpy->val);
		cpy = cpy->next;
	}
	return (NULL);
}

char	**get_env_array(t_env *env, int num)
{
	t_env	*cpy;
	char	**envp;
	int		i;

	if (!(envp = (char **)malloc(sizeof(char *) * num)))
		return (0);
	cpy = env;
	i = -1;
	while (cpy)
	{
		envp[++i] = cpy->data;
		cpy = cpy->next;
	}
	envp[++i] = NULL;
	return (envp);
}
