/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 06:39:22 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/20 05:07:25 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_stat_cd(t_cmd	*data, char	*path)
{
	struct stat	buff;

	if (stat(path, &buff) == -1)
		printt_error1("minishell", data->av[0], \
			"No such file or directory", 1);
	else if (!S_ISDIR(buff.st_mode))
		printt_error1("minishell", data->av[0], "Not a directory", 1);
}

void	new_pwd(const char	*str)
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
			path = getcwd(buff, 10);
			if (path != NULL)
			{
				free(g_codes.g_env[i]);
				g_codes.g_env[i] = ft_strjoin(str, path);
				free(path);
			}
		}
		i++;
	}
}

void	add_oldpwd(char	*str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_codes.g_env[i])
	{
		if (ft_strncmp(g_codes.g_env[i], "OLDPWD=", 7) == 0)
		{
			tmp = ft_substr(str, 4, ft_strlen(str));
			free(g_codes.g_env[i]);
			g_codes.g_env[i] = ft_strjoin("OLDPWD=", tmp);
			free(tmp);
		}
		i++;
	}
}

void	mini_function(char *pwd)
{
	add_oldpwd(pwd);
	new_pwd("PWD=");
}

void	cd(t_cmd	*data)
{
	char	*pwd;
	int		dir;
	int		i;

	if (!data->av[1])
	{
		printt_error1("./minishell", "cd", \
			"with only a relative or absolute path", 1);
		return ;
	}
	i = 0;
	while (g_codes.g_env[i])
	{
		if (ft_strncmp(g_codes.g_env[i], "PWD=", 4) == 0)
			pwd = g_codes.g_env[i];
		i++;
	}
	dir = chdir(data->av[1]);
	if (dir != 0)
	{
		check_stat_cd(data, data->av[1]);
		return ;
	}
	mini_function(pwd);
}
