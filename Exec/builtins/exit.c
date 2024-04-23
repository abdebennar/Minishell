/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:09:25 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/21 17:14:46 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_atoll(char *str, int *err)
{
	unsigned long long	num;
	int					sign;

	(1) && (sign = 1, num = 0);
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str++ - '0';
		if (((num > LLONG_MAX) && (sign > 0))
			|| ((num - 1 > LLONG_MAX) && (sign < 0)))
		{
			*err = 1;
			return (-1);
		}
	}
	if (*str)
	{
		*err = 1;
		return (255);
	}
	return ((long long)num * sign);
}

void	_exit_(char **cmd)
{
	long long	num;
	int			err;

	if (!cmd[1])
		exit(0);
	if (cmd[2])
	{
		printf("exit\nbash: exit: too many arguments\n");
		exit(1);
	}
	err = 0;
	num = ft_atoll(cmd[1], &err);
	if (err)
	{
		printf("exit\nbash: exit: %s: numeric argument required", cmd[1]);
		exit(num);
	}
	if (num >= 0)
		num = num % 256;
	else
	{
		num = 256 + num;
		if (num > 255)
			num = 256 - (num % 256);
	}
	exit(num);
}
