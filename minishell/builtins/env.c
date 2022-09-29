/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:24:58 by aelandal          #+#    #+#             */
/*   Updated: 2022/09/22 11:58:26 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_chr_char(char *str, char c)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (-1);
}

void    env()
{
    int i = 0;
    while (g_codes.g_env[i])
    {
        if (ft_chr_char(g_codes.g_env[i], '=') == 1)
            printf("%s\n", g_codes.g_env[i]);
        i++;
    }
}
