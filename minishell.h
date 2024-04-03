/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:21:20 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/03 06:34:06 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_data
{
	void			*data;
	struct s_data	*next;
}	t_data;

typedef struct s_env
{
	char			*env;
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

//ft_lendupcmp
int	ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
int	ft_strlen(char *str);

//ft_strjoin
char	*ft_strjoin(char *s1, char *s2);

//my_malloc
void	*my_malloc(size_t size, int mode);
