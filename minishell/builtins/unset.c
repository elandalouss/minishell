/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:04:30 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/07 09:52:11 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

char	**copy_2d(char **str1, char **str2)
{
	int	i;

	i = 0;
	while (str2[i])
	{
		str1[i] = ft_strdup(str2[i]);
		i++;
	}
	return (str1);
}

int	check_builtin_error(t_cmd	*data)
{
	int	i;
	int	j;

	i = 1;
	while (data->av[i])
	{
		j = 0;
		while (data->av[i][j])
		{
			if ((data->av[i][j] < 'a' || data->av[i][j] > 'z')
				&& (data->av[i][j] < 'A' || data->av[i][j] > 'Z')
					&& data->av[i][j] != '#' && data->av[i][j] != '_')
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

void	unset(t_cmd	*data)
{
	char	**tmp;
	int		ln_env_cnt;
	int		j;
	int		i;
	int		k;

	i = 1;
	ln_env_cnt = 0;
	if (check_builtin_error(data) == -1)
		printt_error1("./minishell: unset", data->av[i], \
			": not a valid identifier", 1);
	while (g_codes.g_env[ln_env_cnt])
		ln_env_cnt++;
	while (data->av[i])
	{
		data->av[i] = ft_strjoin(data->av[i], "=");
		j = 0;
		while (j < ln_env_cnt && g_codes.g_env[j])
		{
			if (ft_strncmp(g_codes.g_env[j], data->av[i], \
				ft_strlen(data->av[i])) == 0)
			{
				tmp = ft_calloc(ln_env_cnt + 1, sizeof(char *));
				if (!tmp)
				{
					ft_putendl_fd("allocation failed", 2);
					exit (1);
				}
				tmp = copy_2d(tmp, g_codes.g_env);
				free_2d(g_codes.g_env, ln_env_cnt);
				ln_env_cnt--;
				g_codes.g_env = ft_calloc(ln_env_cnt + 1, sizeof(char *));
				if (!g_codes.g_env)
				{
					ft_putendl_fd("allocation failed", 2);
					exit (1);
				}
				k = 0;
				while (tmp[k])
				{
					if (k < j)
						g_codes.g_env[k] = ft_strdup(tmp[k]);
					else if (tmp[k + 1])
						g_codes.g_env[k] = ft_strdup(tmp[k + 1]);
					k++;
				}
			}
			j++;
		}
		i++;
	}
}
