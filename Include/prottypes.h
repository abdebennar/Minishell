/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prottypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:16:16 by abennar           #+#    #+#             */
/*   Updated: 2024/04/21 18:00:16 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf
#include <unistd.h> //write - close - fork - dup2 - chdir
#include <stdlib.h> //malloc 
#include <stdbool.h> //true && false
#include <limits.h> //INT_MAX
#include <fcntl.h> //open
#include <dirent.h> //opendir
#include <readline/readline.h> // readline
#include <readline/history.h> // readline history
// #include "minishell.h"

//ft_lendupcmp
int	ft_strcmp(char *s1, char *s2);

//ft_strjoin
char	*ft_strjoin(char *s1, char *s2);

//my_malloc
void	*my_malloc(size_t size, int mode);

//quotes
char	*d_q(char *raw, int *index);
char	*s_q(char *raw, int *index);
char	*add_c(char *str, char c);

//builtins -> env
int	find_c(char *str, char c);

char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr( char const *str, unsigned int start, size_t len);

void	print_tok(t_token tok);
void	*my_malloc(size_t size, int mode);
void	add_redir_back(t_redir *node, t_redir **list);
void	add_node_back(t_node *node, t_node **list);
char	*get_next_word(char *str, int *i, t_token tok);
int		get_cmd_area(char *s, int start);
void	add_node_back(t_node *node, t_node **list);
void	Parsing(char *cmd);
bool	low_pre(t_token tok);
int		skip_quaout(char *s, char c);
void	lst_iter(t_node	*lst, void (*f)(t_node *));
void	get_args(t_node *node);
void	top_push(t_node **src, t_node **dest);
void	back_push(t_node **src, t_node **dest);



t_node	*infix_to_postfix(t_node **lst);
t_node	*postfix_to_prefex(t_node *node);
t_node	*tree(t_node	*node);
t_token	get_token(char c1, char c2);
t_node	*lexer(char *cmd);
t_redir	*new_redir(char *file, t_token tok);
t_node	*new_node(char *cmd, t_redir *redir, t_token tok, int pre);