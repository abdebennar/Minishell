/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:17:54 by abennar           #+#    #+#             */
/*   Updated: 2024/05/28 19:55:50 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tok_push(t_node **head, t_node **postfix, t_node **tk_st)
{
	while ((*tk_st) && ((*tk_st)->pre > (*head)->pre
			|| ((*tk_st)->pre == (*head)->pre && (*tk_st)->tok != PIPE)))
	{
		back_push(tk_st, postfix);
	}
	top_push(head, tk_st);
}

static void	par_push(t_node **head, t_node **postfix, t_node **tk_st)
{
	t_node	*trash;

	trash = NULL;
	top_push(head, &trash);
	while ((*tk_st) && (*tk_st)->tok != LPR)
		back_push(tk_st, postfix);
	top_push(tk_st, &trash);
}

t_node	*infix_to_postfix(t_node **lst)
{
	t_node	*head;
	t_node	*token_stack;
	t_node	*postfix;

	(1337) && (head = NULL, token_stack = NULL, postfix = NULL);
	head = *lst;
	while (head)
	{
		if (head->tok == NOT)
			back_push(&head, &postfix);
		else if (head->tok != LPR && head->tok != RPR)
			tok_push(&head, &postfix, &token_stack);
		else if (head->tok == LPR)
			top_push(&head, &token_stack);
		else if (head->tok == RPR)
			par_push(&head, &postfix, &token_stack);
	}
	while (token_stack)
		back_push(&token_stack, &postfix);
	return (postfix);
}
