/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:08:54 by abennar           #+#    #+#             */
/*   Updated: 2024/05/23 15:05:47 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static t_uint	cmd_len(char *str)
{
	t_uint	len;
	t_uint	i;
	
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

static t_uint	del_sp(char *cmd, char q)
{
	t_uint i;

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

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\t')
			cmd[i] = ' ';
		if ((cmd[i] == '"' || cmd[i] == '\'') && cmd[i + 1])
		{
			i += del_sp((cmd + i + 1), cmd[i]);
		}
		i++;
	}
	
}

static void	reset_sp(char **args)
{
	t_uint i;
	t_uint j;

	i = 0;
	while (args[i])
	{
		j = 0;
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
	t_uint	len;
	char	*cmd;
	char	**args;
	char	*full_cmd;
	t_uint	i;

	full_cmd = node->full_cmd;
	len = cmd_len(full_cmd);
	cmd = my_malloc(sizeof(char) * len + 1, ALLOC, 0);
	len = 0;
	i = 0;
	while (full_cmd[len])
	{
		if (full_cmd[len] != '\177')
		{
			cmd[i] = full_cmd[len];
			i++;
		}
		len++;
	}
	cmd[i] = '\0';
	arg_space(cmd);
	args = ft_split(cmd, " ", 0);
	reset_sp(args);
	node->cmd = args;
}
