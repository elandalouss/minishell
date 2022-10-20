/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:45:17 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/20 05:19:07 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cwd(void)
{
	int		i;
	char	*str;

	i = 0;
	while (g_codes.g_env[i])
	{
		if (ft_strncmp(g_codes.g_env[i], "PWD=", 4) == 0)
		{
			str = ft_substr(g_codes.g_env[i], 4, \
				ft_strlen(g_codes.g_env[i]));
			printf("%s\n", str);
			free(str);
			break ;
		}
		i++;
	}
}

void	pwd(void)
{
	char	*test;
	char	*res;

	test = NULL;
	res = getcwd(test, 10);
	if (res != NULL)
	{
		printf("%s\n", res);
		free(res);
	}
	else
		cwd();
}
