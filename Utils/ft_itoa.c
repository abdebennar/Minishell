/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:05:20 by abennar           #+#    #+#             */
/*   Updated: 2024/05/04 17:16:45 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_digits(long n)
{
	size_t	i;

	i = 1;
	while (n / 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ascii;
	size_t	digits;
	long	nb;

	nb = n;
	digits = count_digits(nb);
	if (n < 0)
	{
		digits++;
		nb *= -1;
	}
	ascii = my_malloc(sizeof(char) * digits + 1, 1, 1);
	if (!ascii)
		return (NULL);
	*(ascii + (digits--)) = '\0';
	ascii[0] = '0';
	while (nb)
	{
		*(ascii + (digits--)) = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n < 0)
		ascii[0] = '-';
	return (ascii);
}
