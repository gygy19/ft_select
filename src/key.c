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

#include "select.h"

#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <sys/ioctl.h>

void		return_value(void)
{
	t_select *s;
	int i;
	int first;

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

void		print_cursor(int key)
{
	if (key == KEYDOWN)
		CS->cursor_y++;
	if (key == KEYUP)
		CS->cursor_y--;
	if (key == KEYRIGHT)
		CS->cursor_x++;
	if (key == KEYLEFT)
		CS->cursor_x--;
	if (CS->cursor_x == 0 && CS->cursor_y < 0)
	{
		CS->cursor_x = CS->size_x - 1;
		CS->cursor_y = CS->size_y - 1;
	}
	if ((((CS->cursor_x + 1) * CS->size_y) - (CS->size_y - CS->cursor_y)) >= (CS->size - 1))
	{
		if (key == KEYDOWN)
		{
			CS->cursor_x = 0;
			CS->cursor_y = 0;
		}
		if (key == KEYRIGHT || key == KEYLEFT)
			CS->cursor_x = 0;
		else if (key == KEYUP)
			print_cursor(KEYUP);
		else
		{
			CS->cursor_x = 0;
		}
	}
	if (CS->cursor_y > (CS->size_y - 1))
	{
		CS->cursor_y = 0;
		CS->cursor_x++;
	}
	if (CS->cursor_x > (CS->size_x - 1))
		CS->cursor_x = 0;
	if (CS->cursor_y < 0)
	{
		CS->cursor_y = CS->size_y - 1;
		CS->cursor_x--;
	}
	if (CS->cursor_x < 0)
	{
		CS->cursor_x = CS->size_x - 1;
		if ((((CS->cursor_x + 1) * CS->size_y) - (CS->size_y - CS->cursor_y)) >= (CS->size - 1))
			print_cursor(KEYLEFT);
	}
	if (CS->selected[(((CS->cursor_x + 1) * CS->size_y) - (CS->size_y - CS->cursor_y))] == -1)
		print_cursor(key);
}

int		get_next_key(void)
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

size_t		get_size(void)
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

void	process(void)
{
	int key;

	ft_putstr_fd("\033[H", FD);
	print_length(CS, 0, get_size(), NULL);
	key = get_next_key();
	if (DIRECTION)
		print_cursor(key);
	else if (key == SPACE)
		print_select();
	else if (DELETE_KEY)
		delete_value();
	else if (key == ENTER)
	{
		reset_term(CS->term);
		return_value();
		exit(0);
	}
	if (key == ESC || key == ENTER)
		return ;
	/*KEY*/
	//up : 183
	//down : 184
	//left : 186
	//right : 185
	//space : 45
	//enter : 23
	//delete : 140 & 295
	//echape : 40
	process();
}
