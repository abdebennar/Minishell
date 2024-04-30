/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:43:59 by abennar           #+#    #+#             */
/*   Updated: 2024/04/30 15:27:29 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char **copy(char **str, int extra_size)
{
	int	l_cnt;
	char **new;
	int i;
	int j;
	
	l_cnt = 0;
	while (str[l_cnt])
		l_cnt++;

	new = my_malloc((l_cnt + 1 + extra_size) * sizeof (char *), ALLOC, 1);

	i = 0;
	j = 0;
	while (extra_size)
		j++;
	while (str[i])
	{
		l_cnt = ft_strlen(str[i]);
		new[i] = my_malloc(l_cnt + 1, ALLOC, 1);
		ft_strcpy(new[j], str[i]);
		i++;
		j++;
	}
	new[i] = NULL;
	return (new);
}

void	add_env()
{
	t_env	*tmp;

	if (!node || !list)
		return;
	if (!*list)
	{
		*list = node;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_env	*env_init(char **envp)
{
	int		i;
	t_env	*env;
	t_env	*new;
	char	*full_env;
	char	*var;
	char	*value;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		full_env = ft_strdup(envp[i], 1);
		var = ft_substr(envp[i],0, var_len(envp[i]), 1);
		value = ft_substr(envp[i], var_len(envp[i]) + 1, ft_strlen(envp[i]), 1);
		new = new_env(full_env, var, value);
		addback_env(new, &env);
		i++;
	}
	return (env);
}

//gcc Parsing/init.c -IInclude/ utils/* -g3 

// int main(int argc, char **args, char **envp)
// {
// 	t_env *env;
// 	env  = env_init(envp);

// 	while (env)
// 	{
// 		// printf("%s", env->var);
// 		printf("%s\n", env->value);
// 		env = env->next;
// 	}
	
// }