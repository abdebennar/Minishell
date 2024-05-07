/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:17:54 by abennar           #+#    #+#             */
/*   Updated: 2024/04/24 05:01:05 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

t_node	*infix_to_postfix(t_node **lst)
{
	t_node	*head;
	t_node	*token_stack = NULL;
	t_node	*postfix = NULL;
	t_node	*trash = NULL;

	head = *lst;
	while (head)
	{
		if (head->tok == NOT)
			back_push(&head, &postfix);		
		else if (head->tok != LPR && head->tok != RPR)
		{
			while (token_stack && token_stack->pre >= head->pre)
				back_push(&token_stack, &postfix);
			top_push(&head, &token_stack);
		}
		else if (head->tok == LPR)
			top_push(&head, &token_stack);
		else if (head->tok == RPR)
		{
			top_push(&head, &trash);
			while (token_stack->tok != LPR)
				back_push(&token_stack, &postfix);
			top_push(&token_stack, &trash);
		}
	}
	while (token_stack)
		back_push(&token_stack, &postfix);
	return (postfix);
}