/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:12:10 by abennar           #+#    #+#             */
/*   Updated: 2024/05/15 17:47:46 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int check_var(char *str)
{
	if (!((*str >= 'a' && *str <= 'z')
		|| (*str >= 'A' && *str <= 'Z') || (*str == '_')))
		return (-1);
	while(*(++str))
	{
		if (*str == '+' && *(str + 1) == '=')
			return (0);
		else if (*str == '=')
			return (0);
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
    var = my_malloc(1, counter, 0);
    i = 0;
	while (s[i] && s[i] != c)
	{
		var[i] = s[i], i++;
	}
	var[i] = 0;
	return (var);
}

static void	swap_env(char **str1, char **str2)
{
	char *tmp;
	
	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

static char **sort_env(void)
{
	extern char **environ;
	char		**ptr;
	char		**tmp;
	char		**tmp2;

	ptr  = copy(environ, false, 0);
	tmp = ptr;
	while(*tmp)
	{
		tmp2 = (tmp + 1);
		while(*tmp2)
		{
			if (ft_strcmp(*tmp, *tmp2) > 0)
				swap_env(&(*tmp), &(*tmp2));
			tmp2++;
		}
		tmp++;
	}
	return (ptr);
}

void	export_args(char *new_var)
{
	extern char **environ;

	if (ft_strchr(new_var, '='))
	{
		if (*(new_var + get_c(new_var) -  1) == '+')
			_setenv(ft_substr(new_var, 0, get_c(new_var) - 1, 0),
			ft_strjoin(getenv(ft_substr(new_var, 0, get_c(new_var) - 1, 0)), 
			ft_strdup((new_var + get_c(new_var) + 1), 0), 0));
		else
			_setenv(ft_substr(new_var, 0, get_c(new_var), 0), 
			ft_strdup((new_var + get_c(new_var) + 1), 0));
	}
	else 
		_setenv(new_var, NULL);
}

static void	show_export(void)
{
	char **tmp;

	tmp = sort_env();
	while (*tmp)
	{
		if (ft_strncmp(*tmp, "?", get_c(*tmp)))
		{
			if (ft_strchr(*tmp, '=') && ft_strncmp(*tmp, "_", get_c(*tmp)))
				printf("declare -x %s=\"%s\"\n", ft_substr(*tmp, 0, 
					get_c(*tmp), 0), ft_strdup((*tmp + get_c(*tmp) + 1), 0));
			else if (!ft_strchr(*tmp, '='))
				printf("declare -x %s\n", *tmp);
		}
		tmp++;
	}
}

void	_export_(t_node *node)
{
	char	**cmd;

	cmd = node->cmd;
	_setenv("?", ft_itoa(0));
	if (!cmd[1])
		show_export();
	else
		while(*(++cmd))
		{
			if (check_var(ft_substr(*cmd, 0, get_c(*cmd) + 1, 0)))
			{
				put_err("export:");
				put_err(*cmd);
				put_err(": not a valid identifier\n");
				_setenv("?", ft_itoa(1));
				break;
			}
			export_args(*cmd);
		}
}
