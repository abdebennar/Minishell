/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prottypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:16:16 by abennar           #+#    #+#             */
/*   Updated: 2024/04/21 19:50:04 by bel-oirg         ###   ########.fr       */
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
#include "minishell.h"

//quotes
char	*d_q(char *raw, int *index);
char	*s_q(char *raw, int *index);
char	*add_c(char *str, char c);

//builtins -> env
int	find_c(char *str, char c);

//utils ---------
char	**ft_split(char const *s, char c);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strjoin(char *s1, char *s2);
char 	*get_next_word(char *str, int *i, t_token tok);
void	get_args(t_node *node);
void	*my_malloc(size_t size, int mode);

//utils ->mng_cmd
t_token	get_token(const char c1, const char c2);
int		skip_quotes(char *s, char c);
int		get_cmd_area(char *s, int start);

//utils -> ft_str
char	*ft_strdup(const char *s);
int		ft_strlen(char *s);
char	*ft_substr( char const *str, unsigned int start, size_t len);
int		ft_strcmp(char *s1, char *s2);

//utils -> link_lst
t_redir	*new_redir(char *file, t_token tok);
t_node	*new_node(char *cmd, t_redir *redir, t_token tok, int pre);
void	add_redir_back(t_redir *node, t_redir **list);
void	add_node_back(t_node *node, t_node **list);
void	add_redir_back(t_redir *node, t_redir **list);

void	print_tok(t_token tok); //just tmp

//parsing
void	Parsing(char *cmd);
bool	low_pre(t_token tok);
void	lst_iter(t_node	*lst, void (*f)(t_node *));

//algo
t_node	*infix_to_postfix(t_node **lst);

//algo_utils
void	top_push(t_node **src, t_node **dest);
void	back_push(t_node **src, t_node **dest);
t_node	*postfix_to_prefix(t_node *node);

//tree
t_node	*tree(t_node	*node);

//lexer
t_node	*lexer(char *cmd);
