/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:21:20 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/17 01:47:29 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf
#include <unistd.h> //write - close - fork - dup2 - chdir
#include <stdlib.h> //malloc 
#include <stdbool.h> //true && false
#include <limits.h> //INT_MAX
#include <fcntl.h> //open
#include <dirent.h> //opendir

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

typedef enum e_token
{
	PIPE,
	HEREDOC,
	LPR,
	RPR,
	AND,
	OR,
	APPEND,
	OUT,
	IN,
	NOT,
	END
}	t_token;

typedef struct s_redir
{
	t_token			tok;
	// bool			flg;
	char			*file;
	int				fd;
	struct s_redir	*lchild;
	struct s_redir	*rchild;
}	t_redir;

typedef struct s_node
{
	// char			*pre_cmd;
	// int				precedence;
	t_token			tok;
	t_redir			*redirections;
	char			**cmd;
	int				fd[2];
	struct s_node	*lchild;
	struct s_node	*rchild;
}	t_node;

//ft_lendupcmp
int	ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
int	ft_strlen(char *str);

//ft_strjoin
char	*ft_strjoin(char *s1, char *s2);

//my_malloc
void	*my_malloc(size_t size, int mode);

//quotes
char	*d_q(char *raw, int *index);
char	*s_q(char *raw, int *index);
char	*add_c(char *str, char c);