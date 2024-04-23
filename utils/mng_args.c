/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:08:54 by abennar           #+#    #+#             */
/*   Updated: 2024/04/23 20:17:39 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static uint	cmd_len(char *str)
{
	uint	len;
	uint	i;
	
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\177')
			len++;
		i++;
	}
	return (len);
}

static uint	del_sp(char *cmd, char q)
{
	uint i;

	i = 0;
	while (cmd[i] && cmd[i] != q)
	{
		if (cmd[i] == ' ')
			cmd[i] = '\177';
		i++;
	}
	return (i + 1);
}

static void	arg_space(char *cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			i += del_sp((cmd + i + 1), cmd[i]);
		}
		i++;
	}
	
}

static void	reset_sp(char **args)
{
	uint i;
	uint j;

	i = 0;
	j = 0;
	while (args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '\177')
				args[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void	get_args(t_node *node)
{
	uint	len;
	char	*cmd;
	char	**args;
	uint	i;

	len = cmd_len(node->full_cmd);
	cmd = my_malloc(sizeof(char) * len + 1, ALLOC, 0);
	len = 0;
	i = 0;
	while (node->full_cmd[len])
	{
		if (node->full_cmd[len] != '\177')
		{
			cmd[i] = node->full_cmd[len];
			i++;
		}
		len++;
	}
	cmd[i] = '\0';
	arg_space(cmd);
	args = ft_split(cmd, " ", 0);
	reset_sp(args);
	node->cmd = args[0];
	node->args = ++args;
}
