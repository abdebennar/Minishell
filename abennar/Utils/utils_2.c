/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:48:43 by abennar           #+#    #+#             */
/*   Updated: 2024/04/14 13:50:15 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	lst_free(t_data **hold)
// {
// 	t_data	*tmp;
// 	t_data	*ptr;

// 	if (!hold || !*hold)
// 		return ;
// 	tmp = *hold;
// 	while (tmp)
// 	{
// 		ptr = tmp;
// 		tmp = tmp->next;
// 		free(ptr->data);
// 		free(ptr);
// 	}
// 	*hold = NULL;
// }

// void	*my_malloc(size_t size, int mode)
// {
// 	static t_data	*head;
// 	t_data			*node;
// 	void			*data;

// 	if (mode == 1)
// 	{
// 		data = malloc(size);
// 		if (!data)
// 			return (lst_free(&head), exit(1), NULL);
// 		node = malloc(sizeof(t_data));
// 		if (!node)
// 			return (lst_free(&head), exit(1), NULL);
// 		node->data = data;
// 		node->next = NULL;
// 		(head) && (node->next = head);
// 		head = node;
// 		return (data);
// 	}
// 	if (!mode)
// 		lst_free(&head);
// 	return (NULL);
// }