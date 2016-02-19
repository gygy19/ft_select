/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 02:09:54 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/11 02:09:56 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "select.h"

int			sort_az(char **tab, size_t tab_size)
{
	size_t i;
	size_t id;

	i = 0;
	id = -1;
	while (i < tab_size)
	{
		if ((int)id == -1 && tab[i][0] != '\0')
			id = i;
		else if (tab[i][0] != '\0' && id != i)
			if (ft_strcmp(tab[id], tab[i]) >= 0)
				id = i;
		i++;
	}
	return (id);
}

char		**get_new_tab(int size)
{
	char	**new;
	int		i;

	i = 0;
	new = NULL;
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		ft_error_malloc("[get_new_tab] by char **");
	while (new[i])
	{
		new[i] = NULL;
		i++;
	}
	return (new);
}

char		**sort_tab(char **tab, size_t tab_size, int f(char **, size_t))
{
	size_t	id;
	size_t	size_new;
	char	**new_tab;

	size_new = 0;
	new_tab = get_new_tab(tab_size + 1);
	while (size_new < tab_size)
	{
		id = f(tab, tab_size);
		if (tab[id] != NULL)
		{
			new_tab[size_new] = ft_strdup(tab[id]);
			size_new++;
			ft_bzero(tab[id], 1);
		}
	}
	return (new_tab);
}

void		add_args(char **args, t_select *s)
{
	int		i;
	char	**lst_r;

	i = 0;
	while (args[i])
		i++;
	lst_r = sort_tab(args + 1, i - 1, sort_az);
	s->lst = lst_r;
	if (!(s->selected = (int *)malloc(sizeof(int) * (i + 1))))
		ft_error_malloc("[add_args] by int **");
	s->selected[i] = 0;
	s->size = i;
	while (i > 0)
	{
		s->selected[i] = 0;
		i--;
	}
}
