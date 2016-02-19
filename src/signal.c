/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 00:51:03 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/11 00:51:05 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "select.h"

#include <termios.h>
#include <curses.h>
#include <term.h>

void			ctrlc(int sigint)
{
	if (sigint == SIGINT)
	{
		reset_term(TERM);
		exit(0);
	}
}

void			small_size(void)
{
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), FD, tputs_putchar);
	tputs(tgetstr("cd", NULL), FD, tputs_putchar);
	ft_putstr_fd("Size too small\n", FD);
}

int				ig_good_size(size_t x, size_t y, int w, int size)
{
	int nbr;
	int s_x;

	nbr = 0;
	s_x = (int)x;
	while (s_x > 0)
	{
		if (s_x > (w + 1))
			nbr++;
		s_x -= w;
	}
	nbr = nbr * y;
	if (nbr >= size)
		return (1);
	return (0);
}

void			deplace_term(int sigwinch)
{
	if (ig_good_size(get_size_x(), get_size_y(), get_long_work(CS), CS->size))
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), FD, tputs_putchar);
		tputs(tgetstr("cd", NULL), FD, tputs_putchar);
		print_length(CS, get_size_y());
		print_cursor(KEYUP);
		print_cursor(KEYDOWN);
	}
	else
		small_size();
	(void)sigwinch;
}
