/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:45:17 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/08 18:08:14 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cwd(char	**g_env)
{
	int		i;
	char	*path;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], "PWD=", 4) != 0)
			i++;
		else
			break ;
	}
	if (!g_env[i])
		return ;
	path = ft_substr(g_env[i], 4, ft_strlen(g_env[i]));
	printf("%s\n", path);
	free(path);
}

void	pwd(void)
{
	int		i;
	char	*test;
	char	*res;

	test = NULL;
	res = getcwd(test, 10);
	if (res != NULL)
	{
		i = 0;
		while (g_codes.g_env[i])
		{
			if (ft_strncmp(g_codes.g_env[i], "PWD=", 4) == 0)
				printf("%s\n", ft_substr(g_codes.g_env[i], 4, ft_strlen(g_codes.g_env[i])));
			i++;
		}
		// printf("%s\n", res);
		// free(res);
	}
	else
		cwd(g_codes.g_env);
}
