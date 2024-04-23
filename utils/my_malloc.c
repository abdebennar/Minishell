/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:37:28 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/23 18:08:28 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	lst_free(t_data **hold)
{
	t_data	*tmp;
	t_data	*ptr;

	if (!hold || !*hold)
		return ;
	tmp = *hold;
	while (tmp)
	{
		ptr = tmp;
		tmp = tmp->next;
		free(ptr->data);
		ptr->data = NULL;
		free(ptr);
		ptr = NULL;
	}
	*hold = NULL;
}

void	*my_malloc(size_t size, int mode, int group)
{
	static t_data	*head[GB_GROUPS] = {NULL};
	t_data			*node;
	void			*data;

	if (mode == 1)
	{
		data = malloc(size);
		if (!data)
			return (lst_free(&head[group]), exit(1), NULL);
		node = malloc(sizeof(t_data));
		if (!node)
			return (lst_free(&head[group]), exit(1), NULL);
		node->data = data;
		node->next = NULL;
		(head[group]) && (node->next = head[group]);
		head[group] = node;
		return (data);
	}
	if (!mode)
		return (lst_free(&head[group]), NULL);
	return (lst_free(&head[group]), exit(0), NULL);
}
