/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:05:20 by abennar           #+#    #+#             */
/*   Updated: 2024/04/24 17:07:59 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *error, int exit_NO)
{
	printf("%s\n", error);
	my_malloc(0, 0, 0);
	my_malloc(0, 0, 1);
	exit(exit_NO);
}