/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_anv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:34:00 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		copy_env_in_arg_2(char *s, char *str, int m, int *n)
{
	char	*env;
	int		i;
	char	c;
	int		k;

	k = -1;
	i = m;
	while (ft_isalpha(s[m]) || ft_isdigit(s[m]) || s[m] == '_')
		m++;
	c = s[m];
	s[m] = '\0';
	if ((env = find_env(g_shell.env, &s[i])))
	{
		while (env[++k])
		{
			str[*n] = env[k];
			*n += 1;
		}
	}
	s[m] = c;
	return (m);
}

int		copy_env_in_arg(char *s, char *str, int m, int *n)
{
	int		k;

	k = -1;
	if (s[m] == '?' && ++m)
	{
		while (g_shell.ret_val[++k])
		{
			str[*n] = g_shell.ret_val[k];
			*n += 1;
		}
	}
	else if (ft_isalpha(s[m]) || ft_isdigit(s[m]) || s[m] == '_')
		m = copy_env_in_arg_2(s, str, m, n);
	else
	{
		str[*n] = '$';
		*n += 1;
	}
	return (m);
}

int		ft_len_arg_2(char *s, int *i, int true_len)
{
	char	c;
	char	*str;
	int		n;
	int		m;

	m = *i;
	if (s[m] == '?')
		true_len += ft_strlen(g_shell.ret_val);
	else if (ft_isalpha(s[m]) || ft_isdigit(s[m]) || s[m] == '_')
	{
		n = m;
		while (ft_isalpha(s[m]) || ft_isdigit(s[m]) || s[m] == '_')
			m++;
		c = s[m];
		s[m] = '\0';
		if ((str = find_env(g_shell.env, &s[n])))
			true_len += ft_strlen(str);
		s[m--] = c;
	}
	else
		true_len += 2;
	*i = m;
	return (true_len);
}

char	*ft_len_arg(char *s, int len, int *j, char *str)
{
	int		i;
	int		true_len;

	i = -1;
	true_len = 0;
	while (++i < len)
	{
		if (s[i] == '$' && ++i)
			true_len = ft_len_arg_2(s, &i, true_len);
		else
			true_len++;
	}
	*j = true_len;
	str = (char *)malloc(true_len + 1);
	return (str);
}
