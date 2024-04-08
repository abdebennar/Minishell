#include "../minishell.h"

void    update_pwd(char *new, t_env **env)
{
    while(ft_strcmp((*env)->var, "PWD"))
        *env = (*env)->next;
    if (*env)
        (*env)->value = new;
}

void    update_oldpwd(char *new, t_env **env)
{
    while (ft_strcmp((*env)->var, "ODLPWD"))
        *env = (*env)->next;
    (*env) && ((*env)->value = new);
}

void    _cd_(char **cmd, t_env **env)
{
    int 	exit_err;
    char    old_pwd[PATH_MAX];
    char    pwd[PATH_MAX];

    if (cmd[2])
    {
        printf("bash: cd: too many arguments\n");
        exit(1);
    }
    if (!cmd[1])
        cmd[1] = getenv("HOME");
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
