/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:29:22 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/23 18:38:08 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstaddback(t_env **alst, t_env *new)
{
	t_env *ptr;

	if (alst && *alst)
	{
		ptr = *alst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	else if (alst)
		*alst = new;
}

int	is_alphanum(char c)
{
	return ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9'));
}

static int check_var(char *str)
{
	if (!((*str >= 'a' && *str <= 'z')
		|| (*str >= 'A' && *str <= 'Z') || (*str == '_')))	
		return (-1);
	while(++*str)
	{
		if (*str == '+' && *(str + 1) == '\0')
			return (1);
		else if (!(is_alphanum(*str) || (*str == '_')))
			return (-1);
	}
	return (0);
}

char	*get_val(char *s, int c)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i + 1]);
		i++;
	}
	return (NULL);
}

char	*get_var(char *s, int c)
{
	char	*var;
	int		i;
	int     counter;

	i = 0;
	if (s == NULL)
		return (NULL);
	counter = 1;
	while(s[i] && s[i] != c)
	    counter++, i++;
    var = malloc(counter);
    i = 0;
	while (s[i] && s[i] != c)
	{
		var[i] = s[i], i++;
	}
	var[i] = 0;
	return (var);
}

void	swap_env(char **str1, char **str2)
{
	char *tmp;
	
	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

void	sort_env(t_env **raw_env)
{
	t_env	*tmp_env;
	t_env	*tmp_head;
	
	tmp_head = *raw_env;
	while(tmp_head)
	{
		tmp_env = tmp_head->next;
		while(tmp_env)
		{
			if (ft_strcmp(tmp_head->env, tmp_env->env) > 0)
			{
				swap_env(&(tmp_head->env), &(tmp_env->env));
				swap_env(&(tmp_head->var), &(tmp_env->var));
				swap_env(&(tmp_head->value), &(tmp_env->value));
				//maybe you can swap the entire node
				//swap_env(tmp_head, tmp_env);
			}
			tmp_env = tmp_env->next;
		}
		tmp_head = tmp_head->next;
	}
}

void	export_args(t_env **raw_env, char *new_var)
{
	t_env	*new_node;
	char	*value;
	char	*var;
	int		append;

	var = get_var(new_var, '=');
	value = get_val(new_var, '=');
	append = check_var(var);
	if (append < 0)
	{
		printf("export : not valid in this context : %s", var);
		exit(1);
	}
	(append) && (var[ft_strlen(var) - 1] = 0);
	if (is_it_in(*raw_env, new_var))
	{
		(!append) && ((*raw_env)->value = value);
		(append) && ((*raw_env)->value = ft_strjoin((*raw_env)->value, value));
	}
	else
	{
		new_node = my_malloc(sizeof(t_env), 1); // FIX add the group
		new_node->var = var;
		(append && !value) && (value = ft_strdup("")); // 
		new_node->value = value;
		new_node->env = new_var;
		new_node->next = NULL;
		ft_lstaddback(raw_env, new_node);
	}
}

void	show_export(t_env **raw_env)
{
	if (!raw_env)
		return ;
	sort_env(raw_env);
	while (*raw_env)
	{
		if ((*raw_env)->value)
			printf("declare -x %s=\"%s\"\n", (*raw_env)->var, (*raw_env)->value);
		else
			printf("declare -x %s\n", (*raw_env)->var);
		*raw_env = (*raw_env)->next;
	}
}

void	_export_(char **cmd, t_env **raw_env)
{
	if (!cmd[1])
		show_export(raw_env);
	else
	{
		while(*(++cmd))
			export_args(raw_env, *cmd);
	}
}
