/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:45:17 by aelandal          #+#    #+#             */
/*   Updated: 2022/09/22 12:04:31 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    pwd()
{
	int i = 0;
	while (g_codes.g_env[i])
	{
		if (ft_strncmp(g_codes.g_env[i], "PWD=", 4) != 0)
			i++;
		else
			break ;
	}
	if (!g_codes.g_env[i])
		return ;
	printf("%s\n", ft_substr(g_codes.g_env[i], 4, ft_strlen(g_codes.g_env[i])));	
}
