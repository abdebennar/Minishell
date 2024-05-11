/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:16:16 by abennar           #+#    #+#             */
/*   Updated: 2024/05/11 16:35:33 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // printf
# include <unistd.h> //write - close - fork - dup2 - chdir
# include <stdlib.h> //malloc 
# include <stdbool.h> //true && false
# include <limits.h> //INT_MAX
# include <fcntl.h> //open
# include <errno.h> //errno var
# include <dirent.h> //opendir
# include <readline/readline.h> // readline
# include <readline/history.h> // readline history
# include <signal.h>  
# include <ctype.h>
#include <string.h>
# include "prottypes.h"

//utils --------------------------------------------
char	**ft_split(char *s, char *delim, int group);
char	*ft_strtrim(const char *s1, const char *set, int group);
char	*ft_strjoin(char *s1, char *s2, int group);
char	*get_next_word(char *str, int *i, t_token tok);
void	get_args(t_node *node);
void	*my_malloc(size_t size, int mode, int group);
void	_setenv(char *name, char *new_value); // TODO  the setenv function 
char	**copy(char **str, bool  extra_size, int group);
void	add_env();
int		get_c(char *s);
char	*ft_itoa(int n);

//utils ->mng_cmd
t_token	get_token(const char c1, const char c2);
int		skip_quotes(char *s, char c);
int		get_cmd_area(char *s, int start);

//utils ->ft_is
int is_it_in(t_env *raw_env, char *new_var);
int	is_alphanum(char c);

//utils -> ft_str
char	*ft_strdup(char *s, int group);
int		ft_strlen(const char *s);
char	*ft_substr( char *str, unsigned int start, size_t len, int group);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

//utils -> link_lst
t_redir	*new_redir(char *file, t_token tok);
t_node	*new_node(char *cmd, t_redir *redir, t_token tok, int pre);
void	add_redir_back(t_redir *node, t_redir **list);
void	add_node_back(t_node *node, t_node **list);
void	add_redir_back(t_redir *node, t_redir **list);

// utils -> link_lst2
void	ft_lstaddback(t_env **alst, t_env *new);

//utils ->ft_str2
char    *ft_strcpy(char *s1, char *s2);
char	*ft_strdup_len(char *s1, int len, int group);
int		doc_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		find_c(char *str, char c);
void	print_tok(t_token tok); //just tmp

//----------------------------------------------//

//Exec -----------------------------------------
//Exec -> command ------------------------------
char	**_expanding_(t_node **node);
char	*alter_expanding_(char *file_name);
char	*alter_expanding_heredoc(char *file_name);
//Exec -> command -> expanding_helper ------------
char **concatenate_strings(char **str1, char **str2);

//Exec -> command -> exec -------------------
void	_exec_arch_(t_node *node);
void    _exec_(t_node *node);
char	*add_path(char *cmd);
//Exec -> command -> exec_helper --------------
bool	is_builtin(t_node *node);
char	*add_path(char *cmd);
void	reset_fds(t_node **node, int *bk_fd);
int		_exit_stat_(int oldx);
//Exec -> command -> quotes_helpers --------
char	*add_c(char *str, char c, int group);
char	*check_envar(char *raw, int *index);
int		only_identifier(char *str);
int		count_c(char *str, char c);
//Exec -> command -> quotes ----------------
char	*dollar(char *raw, int *index);
char	*s_q(char *raw, int *index);
char	*d_q(char *raw, int *index);
char	*d_q_heredoc(char *raw, int *index);
//Exec -> command -> wildcards -------------
char	*_wildcard_(char *pattern);
char	*prep_w(char *pattern);

//Exec -> builtins
void    _cd_(t_node *node);
void    _echo_(t_node *node);
void	_env_();
void	_exit_(t_node *node);
long long	ft_atoll(char *str, int *err);
void	_export_(t_node *node);
void	_pwd_(void);
void	_unset_(t_node *node);

//Exec -> executor
void	_and_(t_node *node);
void	_or_(t_node *node);
int		_redirections_(t_node **node);
int		_heredoc_(t_redir *alter);
void	_pipe_(t_node *node);
//--------------------------------------------//

//Parsing ------------------------------------
t_node	*parsing(char *line);
bool	low_pre(t_token tok);
void	lst_iter(t_node	*lst, void (*f)(t_node *));

//algo
t_node	*infix_to_postfix(t_node **lst);
t_node	*postfix_to_prefix(t_node *node);

//algo_utils
void	top_push(t_node **src, t_node **dest);
void	back_push(t_node **src, t_node **dest);

//tree
t_node	*tree(t_node	*node);

//lexer
t_node	*lexer(char *cmd);
void	skip_space(char *cmd, int *i);

//syntax -> parse
bool	check_syntax(t_token tok, char *cmd, int i);
//--------------------------------------------//

// urils -> signal
void	sig_ign();
void	sig_allow();
void	heredoc_h(int n);

#endif
