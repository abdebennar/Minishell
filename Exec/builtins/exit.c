/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:09:25 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/26 19:19:53 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

long long	ft_atoll(char *str, int *err)
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
			(err) && (*err = 1);
			return (-1);
		}
	}
	if (*str)
	{
		(err) && (*err = 1);
		return (255);
	}
	return ((long long)num * sign);
}

void	_exit_(t_node *node)
{
	long long	num;
	int			err;
	char		**cmd;

	cmd = node->cmd;
	(!cmd[1]) && (exit(0), 0);
	if (cmd[2])
		return (put_err(EXIT_MANY_ARGS), _setenv("?", ft_itoa(1)));
	(1) && (err = 0, num = ft_atoll(cmd[1], &err));
	if (err)
	{
		write(2, "exit\nshell: exit: ", 18);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, ": numeric argument required\n", 28);
		exit(255);
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
