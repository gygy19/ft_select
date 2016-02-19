/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 23:58:05 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/10 23:58:07 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "select.h"

#include <termios.h>
#include <curses.h>
#include <term.h>

void		return_value(void)
{
	t_select	*s;
	int			i;
	int			first;

	i = 0;
	s = CS;
	first = 1;
	while (s->lst[i])
	{
		if (s->selected[i] == 1)
		{
			if (!first)
				ft_putstr(" ");
			ft_putstr(s->lst[i]);
			first = 0;
		}
		i++;
	}
}

void		print_select(void)
{
	t_select	*s;
	int			pos;

	s = CS;
	pos = ((s->cursor_x + 1) * s->size_y) - (s->size_y - s->cursor_y);
	if (s->selected[pos] == 0)
		s->selected[pos] = 1;
	else
		s->selected[pos] = 0;
	print_cursor(KEYDOWN);
}

int			delete_value(t_select *s)
{
	int			pos;

	s->size--;
	if ((s->size) <= 1)
		return (1);
	pos = ((s->cursor_x + 1) * s->size_y) - (s->size_y - s->cursor_y);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), s->fd, tputs_putchar);
	tputs(tgetstr("cd", NULL), s->fd, tputs_putchar);
	while (s->lst[pos])
	{
		if (s->lst[pos + 1])
		{
			s->selected[pos] = s->selected[pos + 1];
			s->lst[pos] = s->lst[pos + 1];
		}
		else
			s->selected[pos] = -1;
		pos++;
	}
	ft_strdel(&s->lst[pos]);
	s->lst[pos] = NULL;
	s->selected[s->size] = -1;
	print_cursor(KEYUP);
	return (0);
}
