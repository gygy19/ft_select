/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 03:26:43 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/19 03:26:45 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "select.h"

void		put_color_by_length(char *name, int fd, int len, char *color)
{
	int i;

	i = 0;
	while (name[i] && i < len)
	{
		ft_putchar_fd(name[i], fd);
		i++;
	}
	ft_putstr_fd(color, fd);
	while (name[i])
	{
		ft_putchar_fd(name[i], fd);
		i++;
	}
}

void		put_by_len(char *name, int len, int fd, char *color)
{
	ft_putstr(color);
	write(fd, name, len);
	ft_putstr_fd(ENDCOLOR, fd);
}

char		*is_dir(char *name, int fd, int mode, int curs)
{
	int		i;
	int		len_dir;
	char	*tmp;

	i = 0;
	len_dir = 0;
	tmp = name;
	while (name[i])
		if (name[i++] == '/')
			len_dir = i;
	if (len_dir)
	{
		put_by_len(name, len_dir, fd, COLORDIR);
		tmp = name + len_dir;
		if (curs == 1)
			ft_putstr_fd(CURSOR, fd);
		if (mode == 1)
			ft_putstr_fd(SELECTED, fd);
	}
	return (tmp);
}

void		print_color(char *name, int fd, int mode, int curs)
{
	int		len;
	char	*tmp;

	tmp = is_dir(name, fd, mode, curs);
	len = ft_strlen(tmp);
	if (len > 2 && tmp[len - 2] == '.' && tmp[len - 1] == 'c')
	{
		put_color_by_length(tmp, fd, len - 2, COLORC);
	}
	else
		ft_putstr_fd(tmp, fd);
	ft_putstr_fd(ENDCOLOR, fd);
}
