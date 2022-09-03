//#include "../libft/libft.h"

void    qouted_str(char *str, int  *i, char c)
{
    char    n;

    n = 's';
    if (c == '"')
        n = 'd';
    str[*i] = n;
    (*i)++;
    while (str[*i] && str[*i] != c)
    {
        str[*i] = 'q';
        *i += 1;
    }
    if (str[*i] == c)
        str[*i] = n;
    else
        *i -= 1;
}

char    *meta_data(char  *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '<')
            str[i] = 'r';
        else if (str[i] == '>')
            str[i] = 'w';
        else if (str[i] == '|')
            str[i] = 'p';
        else if (str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
           str[i] = 'b';  
        else if (str[i] == '\"' || str[i] == '\'')
            qouted_str(str, &i, str[i]);
        else
            str[i] = 'u';
        i++;
    }
    return (str);
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int ac, char **av)
{
    (void)ac;
   printf("%s\n", av[1]); 
    av[1] = meta_data(av[1]);
    printf("%s\n", av[1]);
    return 0;
}