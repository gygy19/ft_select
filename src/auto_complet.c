/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 04:04:24 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/19 04:04:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

static char		*move_curs(char *autoc, t_select *s)
{
	int	len;
	int	i;
	int	stop;
	int	nbr;

	len = ft_strlen(autoc);
	i = 0;
	stop = 0;
	nbr = 0;
	while (i < s->size && s->lst[i])
	{
		if (ft_strncmp(s->lst[i], autoc, len) == 0)
		{
			nbr++;
			stop = i;
		}
		i++;
	}
	if (nbr == 1)
	{
		s->cursor_x = (stop / (s->size_y));
		s->cursor_y = stop - ((stop / (s->size_y)) * s->size_y);
		ft_strdel(&autoc);
	}
	return (autoc);
}

char			*get_auto_complet(char *autoc, t_select *s, int key)
{
	char	*n;
	char	*tmp;

	if (DIRECTION || DELETE_KEY || key == SPACE)
	{
		if (autoc != NULL)
			ft_strdel(&autoc);
		return (NULL);
	}
	if (autoc == NULL)
	{
		autoc = ft_strnew(2);
	}
	n = ft_strnew(2);
	n[0] = (char)key;
	tmp = ft_strjoin(autoc, n);
	ft_strdel(&autoc);
	ft_strdel(&n);
	return (move_curs(tmp, s));
}
