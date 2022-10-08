/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 06:39:22 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/08 17:52:46 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	old_new_pwd(const char	*str)
{
	int		i;
	char	*buff;
	char	*path;

	buff = NULL;
	i = 0;
	while (g_codes.g_env[i])
	{
		if (ft_strncmp(g_codes.g_env[i], str, ft_strlen(str)) == 0)
		{
			free(g_codes.g_env[i]);
			path = getcwd(buff, 10);
			g_codes.g_env[i] = ft_strjoin(str, path);
			free(path);
		}
		i++;
	}
}

void	cd(t_cmd	*data)
{
	int		dir;

	if (!data->av[1])
	{
		printt_error1("./minishell", "cd", \
			"with only a relative or absolute path", 1);
		return ;
	}
	old_new_pwd("OLDPWD=");
	dir = chdir(data->av[1]);
	if (dir != 0)
	{
		printt_error1("./minishell : cd", data->av[1], \
			"No such file or directory", 1);
		return ;
	}
	old_new_pwd("PWD=");
}
