/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 01:02:43 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/10 03:29:09 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include "select.h"

void	ft_init(char **args, t_select *s)
{
	if ((s->fd = open("/dev/tty", O_RDWR)) == -1)
		return ;
	modif_term(s->term);
	add_args(args, s);
}

int		main(int argc, char **argv)
{
	t_select	*select;

	if (argc < 2)
		return (-1);
	signal(SIGINT, ctrlc);
	signal(SIGWINCH, deplace_term);
	select = CS;
	ft_init(argv, select);
	deplace_term(SIGWINCH);
	process();
	reset_term(select->term);
	return (0);
}
