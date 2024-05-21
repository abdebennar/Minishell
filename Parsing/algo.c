/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:17:54 by abennar           #+#    #+#             */
/*   Updated: 2024/05/21 21:17:10 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

t_node	*infix_to_postfix(t_node **lst)
{
	t_node	*head = NULL;
	t_node	*token_stack = NULL;
	t_node	*postfix = NULL;
	t_node	*trash = NULL;

	if (!lst || !*lst)
		return (NULL);
	head = *lst;
	while (head)
	{
		if (head->tok == NOT)
			back_push(&head, &postfix);		
		else if (head->tok != LPR && head->tok != RPR)
		{
			while (token_stack && (token_stack->pre > head->pre || (token_stack->pre == head->pre && token_stack->tok != PIPE)))
				back_push(&token_stack, &postfix);
			top_push(&head, &token_stack);
		}
		else if (head->tok == LPR)
			top_push(&head, &token_stack);
		else if (head->tok == RPR)
		{
			top_push(&head, &trash);
			printf("this is token_stack %p\n", token_stack);
			while (token_stack->tok != LPR)
				back_push(&token_stack, &postfix);
			top_push(&token_stack, &trash);
		}
	}
	while (token_stack)
		back_push(&token_stack, &postfix);
	return (postfix);
}
