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

int check_quotes_n(char *str)
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

int	count_c(char *str, char c)
{
	int counter;

	counter = 0;
	while (*str)
	{
		if (*str++ == c)
			counter++;
	}
	return (counter);
}

int	check_parral(char *str)
{
	int	index;
	int	r_index;
	char q[2];
	int max_s;

	q[0] = '\'';
	q[1] = '\"';
	index = -1;
	max_s = count_c(str, '\'');
	r_index = strlen(str) - 1;
	while (str[++index])
	{
		if (str[index] == q[0])
		{
		    max_s--;
			while(str[r_index] != q[0])
			{
			    if (str[r_index] == q[1])
			        return (-2);
			   	r_index--;
			}
			printf("r_index %d -- index %d\n", r_index, index);
			if (index == r_index)
				return (-1);
			max_s--;
			if (!max_s)
			    return (0);
		}
		else if (str[index] == q[1])
		{
			while(str[r_index] != q[1])
				r_index--;
			if (index >= r_index)
				return (-1);
		}
	}
	return (0);
}

int main() {
    printf("%d \n", check_parral("l\'\'idsa\"ds\"a"));

    return 0;
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
