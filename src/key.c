/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 23:58:50 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/10 23:58:51 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

#include "select.h"

static void		verif_1(t_select *s, int key)
{
	if (s->cursor_x <= 0 && s->cursor_y < 0)
	{
		s->cursor_x = s->size_x - 1;
		s->cursor_y = s->size_y - 1;
	}
	if ((((s->cursor_x + 1) * s->size_y)
		- (s->size_y - s->cursor_y)) >= (s->size - 1))
	{
		if (key == KEYDOWN)
		{
			s->cursor_x = 0;
			s->cursor_y = 0;
		}
		if (key == KEYRIGHT || key == KEYLEFT)
			s->cursor_x = 0;
		else if (key == KEYUP)
			print_cursor(KEYUP);
		else
		{
			s->cursor_x = 0;
		}
	}
}

static void		verif_2(t_select *s, int key)
{
	if (s->cursor_y > (s->size_y - 1))
	{
		s->cursor_y = 0;
		s->cursor_x++;
	}
	if (s->cursor_x > (s->size_x - 1))
		s->cursor_x = 0;
	if (s->cursor_y < 0)
	{
		s->cursor_y = s->size_y - 1;
		s->cursor_x--;
	}
	if (s->cursor_x < 0)
	{
		s->cursor_x = s->size_x - 1;
		if ((((s->cursor_x + 1) * s->size_y)
			- (s->size_y - s->cursor_y)) >= (s->size - 1))
			print_cursor(KEYLEFT);
	}
	if (s->selected[(((s->cursor_x + 1) * s->size_y)
		- (s->size_y - s->cursor_y))] == -1)
		print_cursor(key);
}

void			print_cursor(int key)
{
	t_select *s;

	s = CS;
	if (key == KEYDOWN)
		s->cursor_y++;
	if (key == KEYUP)
		s->cursor_y--;
	if (key == KEYRIGHT)
		s->cursor_x++;
	if (key == KEYLEFT)
		s->cursor_x--;
	verif_1(s, key);
	verif_2(s, key);
}

int				get_next_key(void)
{
	char	buff[6];
	int		ret;
	int		touch;

	touch = 0;
	while ((ret = read(0, buff, 5)) == 0)
	{
		buff[ret] = '\0';
	}
	buff[ret] = '\0';
	ret = 0;
	while (buff[ret])
	{
		touch += buff[ret];
		ret++;
	}
	return (touch);
}

void			process(void)
{
	int key;

	deplace_term(0);
	key = get_next_key();
	TERM->c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, TCSADRAIN, TERM) == -1)
		return ;
	if (DIRECTION)
		print_cursor(key);
	else if (key == SPACE)
		print_select();
	else if (key == ENTER)
	{
		reset_term(CS->term);
		return_value();
		exit(0);
	}
	else if (DELETE_KEY)
		if (delete_value(CS) == 1)
			return ;
	if (key == ESC)
		return ;
	process();
}
