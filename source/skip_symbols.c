/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:34:22 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libshell.h"

int		skip_space(char *s, int i)
{
	while (ft_memchr(" \t\v\r\n\f", s[i], 6))
		i++;
	return (i);
}

int		skip_quotes(char c1, char c2, char q, int i)
{
	if (c1 != q || (c1 == q && i && c2 == '\\'))
		return (0);
	return (1);
}

int		skip_to_space(char *s, int i)
{
	while (!ft_memchr(" \t\v\r\n\f\0", s[i], 7))
	{
		if (s[i] == '\'' && ++i)
		{
			while (s[i] != '\0' && s[i] != '\'')
				i++;
		}
		else if (s[i] == '\"' && (i == 0 || s[i - 1] != '\\') && ++i)
		{
			while (s[i] != '\0' && !skip_quotes(s[i], s[i - 1], '\"', i))
				i++;
		}
		if (ft_memchr(";|\0", s[i], 3))
			break ;
		else
			i++;
	}
	return (i);
}
