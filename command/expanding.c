/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:29:18 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/09 07:08:43 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	in_d_quotes(char *str)
{
	if (!str)
		return (0);
	if (*str == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (1);
}

int check_quotes(char *str)
{
	int	s_quotes;
	int	d_quotes;

	s_quotes = 0;
	d_quotes = 0;
	while(*str)
	{
		if (*str == '\'')
			s_quotes++;
		else if (*str == '\"')
			d_quotes++;
		str++;
	}
	return (!((s_quotes % 2) || (d_quotes % 2)));
}

int	in_s_quotes(char *str)
{
	if (!str)
		return (0);
	if (*str == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (1);
}

void	_b_expanding_(t_node **node)
{
	char **cmd;
	int	index;

	(*node)->cmd = cmd;
	index = -1;
	while (cmd[++index])
	{
		
	}
}

void	_expanding_(t_node **node, t_env *env)
{
	t_env	*tmp_env;
	int		index;
	
	tmp_env = env;
	while((*node)->cmd)
	{
		index = -1;
		while((*node)->cmd[++index])
		{
			if ((*node)->cmd[index][0] == '$')
			{
				if (!ft_strcmp((*node)->cmd[index], "$?"))
					exit_stat();
				env = tmp_env;
				while (ft_strcmp(&((*node)->cmd[index][1]), env->var))
					env = env->next;
				if (env)
					(*node)->cmd[index] = ft_strdup(env->value);
				else
					(*node)->cmd[index] = ft_strdup("");
			}
		}
		*node = (*node)->rchild;
	}
}
