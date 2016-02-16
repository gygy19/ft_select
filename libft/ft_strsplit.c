/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 04:47:19 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/06 23:02:38 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*delim(char *s, char c)
{
	if (s)
	{
		while (*s == c)
		{
			s++;
		}
		return (s);
	}
	return (NULL);
}

static int	size_occus(char *s, char c)
{
	int	size;

	size = 0;
	if (s)
	{
		while (*s)
		{
			if (*s == c)
				break ;
			s++;
			size++;
		}
	}
	return (size);
}

static char	**split(char **result, char *s, char c)
{
	int		x;
	int		y;
	char	*tmp;

	x = 0;
	y = 0;
	while (s && c && *s)
	{
		if (*s == c)
		{
			if ((s = delim((char*)s, c)) && !*s)
				break ;
			result[y][x] = '\0';
			y++;
			tmp = ft_strnew(size_occus((char*)s, c));
			result[y] = tmp;
			x = 0;
		}
		if (*s != c)
			result[y][x] = *s;
		s++;
		x++;
	}
	return (result);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**result;
	int		len;

	if (!s)
		return (NULL);
	result = NULL;
	len = (ft_lenbychar((char*)s, c)) * 2;
	if (!(result = (char **)malloc(sizeof(char*) *
		(ft_lenbychar((char*)s, c)) * 2)))
		return (NULL);
	s = delim((char*)s, c);
	if (!*s)
		return (result);
	result[0] = ft_strnew(size_occus((char*)s, c));
	result = split(result, (char*)s, c);
	if (result[len] != NULL)
		result[len] = NULL;
	return (result);
}
