/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lenght.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 03:57:02 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/11 03:57:04 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int			get_long_work(t_select *args)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (i < args->size)
	{
		if ((int)(ft_strlen(args->lst[i]) + 1) > len)
			len = ft_strlen(args->lst[i]) + 1;
		i++;
	}
	return (len);
}

int			get_line(int win_size, int long_work)
{
	int line;
	int i;
	int lim;

	line = long_work;
	i = 1;
	lim = long_work - 1;
	while (line < (win_size - lim))
	{
		line += long_work;
		i++;
	}
	return (i);
}

int			get_ll(int line, t_select *args)
{
	int ret;
	int i;
	int o;

	i = 0;
	ret = 1;
	o = 1;
	while (i < args->size)
	{
		if (o > line)
		{
			o = 1;
			ret++;
		}
		o++;
		i++;
	}
	return (ret);
}

int			g_t(char *dir, char *file, int flags)
{
	//char	*tmp;
	(void)dir;
	(void)file;
	(void)flags;
	int		ret;

	ret = 0;
	/*if (flags & FLAG_FF)
	{
		tmp = get_infos(file, dir);
		if (is_lnk(tmp))
			return (1);
		else if (is_dir(tmp))
			return (1);
		else if (is_exe(tmp))
			return (1);
		free(tmp);
	}*/
	return (ret);
}

void		get_x(t_select *args)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (args->lst[i])
	{
		i += args->size_y;
		ret++;
	}
	args->size_x = ret;
}

int			get_vs(int i, int i2, int line)
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

void		print_length(t_select *args, int f, int win_size, char *d)
{
	int		line;
	int		i;
	int		i2;
	int		s;
	int		w;

	w = get_long_work(args);
	line = get_line(win_size, w);
	line = get_ll(line, args);
	args->size_y = line;
	get_x(args);
	int gomme;
	int total;

	gomme = 0;
	total = 0;
	i = 0;
	while (i < line)//ligne en cour
	{
		i2 = i;
		while (args->lst[i2])//id en cour
		{
				s = ((w - ft_strlen(args->lst[i2])) - g_t(d, args->lst[i2], f));
			if (args->selected[i2] == -1)
			{
				i2 += line;
				gomme++;
				continue ;
			}
			total += s + ft_strlen(args->lst[i2]);
			if (args->cursor_y == i && args->cursor_x == get_vs(i, i2, line))
				ft_putstr_fd("\e[4m", FD);
			if (args->selected[i2] == 1)
				ft_putstr_fd("\e[1;32m", FD);
			if (args->selected[i2] != -1)
				ft_putstr_fd(args->lst[i2], FD);
			if (args->selected[i2] == 1 || (args->cursor_y == i && args->cursor_x == get_vs(i, i2, line)))
				ft_putstr_fd("\e[00m", args->fd);
			//put_color_type_length(d, args->lst[i2], f);
			if (i2 < (args->size))
				while (s-- > 0)
					ft_putchar_fd(' ', FD);
			i2 += line;//line = a hauteur max
		}
		while (total < win_size)
		{
			ft_putchar_fd(' ', FD);
			total++;
		}
		total = 0;
		ft_putstr_fd("\n", FD);
		i++;
	}
	if (gomme)
		while (total < win_size)
		{
			ft_putchar_fd(' ', FD);
			total++;
		}
}
