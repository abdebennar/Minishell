#include "../minishell.h"

bool check_pattern(char *str, char *pattern)
{
    if (!*str && !*pattern)
        return true;

    while (*pattern == '*' && *(pattern + 1) == '*')
        pattern++;

    if (!*str && *pattern == '*' && !*(pattern + 1))
        return true;

    if (*str == *pattern)
        return check_pattern(str + 1, pattern + 1);

    if (*pattern == '*')
        return check_pattern(str + 1, pattern) || check_pattern(str, pattern + 1);

    return false;
}

void    _wildcard_()
{
    struct dirent   *entry;
    char            *extracted;
    DIR             *dir;

    dir = opendir(".");
    if (!dir)
    {
        perror("opendir");
        return ;
    }
    while (1)
    {
        entry = readdir(dir);
        if (!entry)
            break;
        if (check_pattern(entry->d_name, "*t*"))
        {
            extracted = ft_strjoin(extracted, " ");
            extracted = ft_strjoin(extracted, entry->d_name);
        }
    }
    printf("%s -\n", extracted);
}

// int main()
// {
//     if (check_pattern("quoe", "*b*"))
//         printf("YEpA\n");
//     _wildcard_();
// }