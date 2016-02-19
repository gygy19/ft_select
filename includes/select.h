/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 02:49:52 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/10 03:11:49 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# include <termios.h>

# include "libft.h"

# define CS create_select()
# define FD (CS->fd)
# define TERM (CS->term)
# define LIST (CS->lst)
# define KEYUP 183
# define KEYDOWN 184
# define KEYRIGHT 185
# define KEYLEFT 186
# define SPACE 32
# define ENTER 10
# define ESC 27

# define CURSOR "\e[4m"
# define SELECTED "\e[1;32m"
# define ENDCOLOR "\e[00m"

# define DIRECTION (key == 183 || key == 184 || key == 185 || key == 186)
# define DELETE_KEY (key == 140 || key == 295)

typedef struct		s_select
{
	struct termios	*term;
	int				fd;
	char			**lst;
	int				size;
	int				cursor_x;
	int				cursor_y;
	int				size_x;
	int				size_y;
	int				*selected;
}					t_select;

int					modif_term(struct termios *term);
int					reset_term(struct termios *term);
t_select			*create_select(void);
int					tputs_putchar(int c);
void				ft_error_malloc(char *str);
int					get_next_key(void);
void				process(void);
void				ft_error(char *str);
void				ctrlc(int sigint);
void				ctrlz(int sigquit);
void				print_lst(void);
void				print_select(void);
int					delete_value(t_select *s);
void				print_cursor(int key);
void				add_args(char **args, t_select *s);
void				print_length(t_select *args, int win_size);
size_t				get_size_x(void);
size_t				get_size_y(void);
void				deplace_term(int sigwinch);
void				print_cursor(int key);
void				return_value(void);
int					get_long_work(t_select *args);

#endif
