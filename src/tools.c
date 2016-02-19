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
#include <sys/ioctl.h>

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

size_t			get_size_x(void)
{
	size_t			size;
	struct winsize	*w;

	if (!(w = malloc(sizeof(struct winsize))))
		ft_error_malloc("[get_size] struct winsize");
	ioctl(0, TIOCGWINSZ, w);
	size = (size_t)w->ws_col;
	free(w);
	return (size);
}

size_t			get_size_y(void)
{
	size_t			size;
	struct winsize	*w;

	if (!(w = malloc(sizeof(struct winsize))))
		ft_error_malloc("[get_size] struct winsize");
	ioctl(0, TIOCGWINSZ, w);
	size = (size_t)w->ws_row;
	free(w);
	return (size);
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
