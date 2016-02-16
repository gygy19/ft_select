/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 23:58:19 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/10 23:58:20 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

#include <stdlib.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>

int		modif_term(struct termios *term)
{
	if (tgetent(NULL, getenv("TERM")) != 1)
		ft_error("[modif_term] Unknow TERM variable\n");
	if (tcgetattr(0, term) == -1)
		ft_error("[modif_term] Failed request tcgetattr!\n");
	tputs(tgetstr("ti", NULL), 1, tputs_putchar);
	tputs(tgetstr("vi", NULL), 1, tputs_putchar);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (0);
	return (1);
}

int		reset_term(struct termios *term)
{
	if (tcgetattr(0, term) == -1)
		ft_error("[reset_term] Failed request tcgetattr!\n");
	tputs(tgetstr("te", NULL), FD, tputs_putchar);
	tputs(tgetstr("ve", NULL), FD, tputs_putchar);
	tputs(tgetstr("te", NULL), FD, tputs_putchar);
	term->c_lflag = (ICANON | ECHO | ISIG);
	if (tcsetattr(0, 0, term) == -1)
		return (0);
	close(FD);
	return (1);
}
