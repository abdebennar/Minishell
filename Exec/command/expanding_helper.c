/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 01:54:13 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/29 19:03:13 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strings(char **str1)
{
	int	counter;

	counter = 0;
	while (str1 && str1[counter])
		counter++;
	return (counter);
}

char	**concatenate_strings(char **str1, char **str2)
{
	char	**out;
	int		out_index;
	int		index1;
	int		index2;

	if (!str1 && !str2)
		return (NULL);
	index1 = count_strings(str1);
	index2 = count_strings(str2);
	out = my_malloc(sizeof(char *) * (index1 + index2 + 1), 1, 0);
	out_index = 0;
	while (str1 && str1[out_index])
	{
		out[out_index] = str1[out_index];
		out_index++;
	}
	while (str2 && str2[out_index - index1])
	{
		out[out_index] = str2[out_index - index1];
		out_index++;
	}
	out[out_index] = NULL;
	return (out);
}
