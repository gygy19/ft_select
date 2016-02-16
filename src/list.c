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

void		delete_value(void)
{
	t_select	*s;
	int			pos;

	s = CS;
	pos = ((s->cursor_x + 1) * s->size_y) - (s->size_y - s->cursor_y);
	s->size--;
	if (s->size == 0)
	{
		reset_term(s->term);
		exit(0);
	}
	while (s->lst[pos])
	{
		if (s->lst[pos + 1])
			s->lst[pos] = s->lst[pos + 1];
		pos++;
	}
	free(s->lst[pos]);
	s->lst[pos] = NULL;
	s->selected[s->size] = -1;
	print_cursor(KEYUP);
	pos = ((s->cursor_x + 1) * s->size_y) - (s->size_y - s->cursor_y);
	//while (s->cursor <= s->size && s->selected[s->cursor] == -1)
	//	s->cursor++;
}

/*
void		print_lst(void)
{
	t_select	*s;
	int			i;
	int			lclean;

	s = CS;
	i = 0;
	lclean = 0;
	while (s->lst[i])
	{
		if (s->selected[i] == -1)
		{
			i++;
			lclean++;
			continue ;
		}
		if (s->cursor == i)
			ft_putstr_fd(CURSOR, s->fd);
		if (s->selected[i] == 1)
			ft_putstr_fd(SELECTED, s->fd);
		ft_putstr_fd(s->lst[i], s->fd);
		if (s->cursor == i || s->selected[i] == 1)
			ft_putstr_fd(ENDCOLOR, s->fd);
		ft_putstr_fd("\n", s->fd);
		i++;
	}
	while (lclean)
	{
		ft_putstr_fd("                                                          \n", s->fd);
		lclean--;
	}
}*/