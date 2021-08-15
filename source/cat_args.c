/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:31:46 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:32:11 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		ft_double_quotes(char *s, char *str, int m, int *i)
{
	int		n;
	int		j;

	n = *i;
	j = ft_strlen(s);
	if (s[m] == '\"' && (m == 0 || s[m - 1] != '\\') && ++m > -1)
	{
		g_shell.quotes = 2;
		while (m < j)
		{
			if (s[m] == '\"' && ++m)
				break ;
			else if (s[m] == '$' && ++m)
				m = copy_env_in_arg(s, str, m, &n);
			else if (m < j - 1 && s[m] == '\\')
			{
				m++;
				str[n++] = s[m++];
			}
			else
				str[n++] = s[m++];
		}
	}
	*i = n;
	return (m);
}

int		ft_single_quotes(char *s, char *str, int m, int *i)
{
	int		n;
	int		j;

	n = *i;
	j = ft_strlen(s);
	if (s[m] == '\'' && (m == 0 || s[m - 1] != '\\') && ++m > -1)
	{
		g_shell.quotes = 1;
		while (m < j)
		{
			if (s[m] == '\'' && ++m)
				break ;
			else
				str[n++] = s[m++];
		}
	}
	*i = n;
	return (m);
}

char	*ft_subarg(char *s, int j, int n, int m)
{
	char	*str;
	int		len;

	str = NULL;
	if (!(str = ft_len_arg(s, j, &len, str)))
		return (0);
	ft_memset(str, ' ', len);
	str[len] = '\0';
	while (m < j && n < len)
	{
		m = ft_double_quotes(s, str, m, &n);
		m = ft_single_quotes(s, str, m, &n);
		if (s[m] == '$' && ++m)
			m = copy_env_in_arg(s, str, m, &n);
		else if (m < j - 1 && s[m] == '\\')
		{
			m++;
			str[n++] = s[m++];
		}
		else
			str[n++] = s[m++];
	}
	str[n] = '\0';
	return (str);
}
