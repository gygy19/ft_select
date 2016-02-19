/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 03:57:02 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/11 03:57:04 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include <curses.h>
#include <term.h>

int				get_long_work(t_select *args)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (i < args->size)
	{
		if (args->selected[i] != -1 && (int)(ft_strlen(args->lst[i]) + 1) > len)
			len = ft_strlen(args->lst[i]) + 1;
		i++;
	}
	return (len);
}

static int		get_x_and_y(t_select *args, int line, int w)
{
	if (line > args->size)
	{
		args->size_y = args->size;
		args->size_x = 1;
		line = args->size;
	}
	else
	{
		args->size_y = line;
		args->size_x = (args->size / line) + 1;
	}
	(void)w;
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), FD, tputs_putchar);
	tputs(tgetstr("cd", NULL), FD, tputs_putchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), FD, tputs_putchar);
	return (line);
}

static int		get_vs(int i, int i2, int line)
{
	int nbr;

	nbr = 0;
	while (i2 != i)
	{
		i2 -= line;
		nbr++;
	}
	return (nbr);
}

static void		print_dir(int i2, int i, int line, t_select *args)
{
	int vs;

	if (args->selected[i2] == -1 || args->lst[i2] == NULL)
		return ;
	vs = get_vs(i, i2, line);
	if (args->cursor_y == i && args->cursor_x == vs)
		ft_putstr_fd(CURSOR, args->fd);
	if (args->selected[i2] == 1)
		ft_putstr_fd(SELECTED, args->fd);
	if (args->selected[i2] != -1)
		print_color(args->lst[i2], args->fd,
			args->selected[i2], args->cursor_y == i && args->cursor_x == vs);
	if ((args->selected[i2] == 1)
		|| (args->cursor_y == i && args->cursor_x == vs))
		ft_putstr_fd(ENDCOLOR, args->fd);
}

void			print_length(t_select *args, int win_size)
{
	int		line;
	int		i;
	int		i2;
	int		s;
	int		w;

	w = get_long_work(args);
	line = win_size;
	line = get_x_and_y(args, line, w);
	i = 0;
	while (i < line)
	{
		i2 = i;
		if (i != 0)
			ft_putstr_fd("\n", args->fd);
		while (i2 < args->size && args->lst[i2])
		{
			s = ((w - ft_strlen(args->lst[i2])));
			print_dir(i2, i, line, args);
			while (i2 < (args->size) && s-- > 0)
				ft_putchar_fd(' ', args->fd);
			i2 += line;
		}
		i++;
	}
}
