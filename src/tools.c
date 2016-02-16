/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 23:58:58 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/10 23:58:59 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "select.h"

t_select		*create_select(void)
{
	static t_select	*s;

	if (!s)
	{
		if (!(s = malloc(sizeof(t_select))))
			ft_error_malloc("[create_select] by struct t_select\n");
		if (!(s->term = malloc(sizeof(struct termios))))
			ft_error_malloc("[create_select] by struct termios\n");
		s->cursor_x = 0;
		s->cursor_y = 0;
	}
	return (s);
}


int				tputs_putchar(int c)
{
	write(FD, &c, 1);
	return (1);
}

void			ft_error_malloc(char *str)
{
	ft_putstr("Error malloc in ");
	ft_putstr(str);
	exit(-1);
}

void			ft_error(char *str)
{
	ft_putstr(str);
	exit(-1);
}