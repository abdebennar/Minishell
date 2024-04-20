/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:17:54 by abennar           #+#    #+#             */
/*   Updated: 2024/04/19 22:15:35 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			push(&head, &postfix);		
		}
		else if (head->tok != LPR && head->tok != RPR)
		{
			while (token_stack && token_stack->pre >= head->pre)
				push(&token_stack, &postfix);
			push(&head, &token_stack);
		}
		else if (head->tok == LPR)
			push(&head, &token_stack);
		else if (head->tok == RPR)
		{

			push(&head, &trash);
			while (token_stack->tok != LPR)
				push(&token_stack, &postfix);
			push(&token_stack, &trash);
		}
		
	}
	while (token_stack)
		push(&token_stack, &postfix);
	
	return (postfix);
}
