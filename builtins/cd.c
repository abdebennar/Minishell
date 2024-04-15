/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:17:06 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/12 11:17:06 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void    update_pwd(char *new_pwd, t_env **env)
{
    t_env   *new_node;

    while (ft_strcmp((*env)->var, "PWD"))
        *env = (*env)->next;
    if (*env)
    {
        (*env)->value = new_pwd;
		new_node->env = ft_strjoin("PWD=", new_pwd);
    }
    else
    {
        new_node = my_malloc(sizeof(t_env), 1);
        new_node->var = ft_strdup("PWD");
		new_node->value = ft_strdup(new_pwd);
		new_node->env = ft_strjoin("PWD=", new_pwd);
		new_node->next = NULL;
		ft_lstaddback(env, new_node);
    }
}

static void    update_oldpwd(char *new_pwd, t_env **env)
{
    t_env   *new_node;

    while (ft_strcmp((*env)->var, "OLDPWD"))
        *env = (*env)->next;
    if (*env)
    {
        (*env)->value = new_pwd;
		new_node->env = ft_strjoin("OLDPWD=", new_pwd);
    }
    else
    {
        new_node = my_malloc(sizeof(t_env), 1);
        new_node->var = ft_strdup("OLDPWD");
		new_node->value = ft_strdup(new_pwd);
		new_node->env = ft_strjoin("OLDPWD=", new_pwd);
		new_node->next = NULL;
		ft_lstaddback(env, new_node);
    }
}

void    _cd_(char **cmd, t_env **env)
{
    char    old_pwd[PATH_MAX];
    char    pwd[PATH_MAX];
    int 	exit_err;

    if (cmd[2])
    {
        printf("bash: cd: too many arguments\n");
        exit(1);
    }
    if (!cmd[1])
        cmd[1] = getenv("HOME");
    else if (ft_strcmp(cmd[1], "-"))
        cmd[1] = getenv("OLDPWD");
    if (getcwd(old_pwd, PATH_MAX))
        return ;
    exit_err = chdir(cmd[1]);
    if (exit_err)
    {
        perror(NULL);
        exit(exit_err);
    }
    if (getcwd(pwd, PATH_MAX))
        return ;
    update_oldpwd(old_pwd, env);
    update_pwd(pwd, env);
}
