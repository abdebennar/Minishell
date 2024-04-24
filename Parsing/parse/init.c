/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:43:59 by abennar           #+#    #+#             */
/*   Updated: 2024/04/24 05:01:08 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	add_env(t_node *node, t_env *env)
{
	while (node)
	{
		node->env = env;
		node = node->right;
	}	
}

int		var_len(char *str)
{
	int i;

	i  = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

t_env	*new_env(char *env, char *var, char *value)
{
	t_env	*new;

	new = my_malloc(sizeof(t_env), ALLOC, 1);
	new->env = env;
	new->value = value;
	new->var = var;
	new->next = NULL;

	return (new);
}

void	addback_env(t_env *node, t_env **list)
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