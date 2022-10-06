/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:55:32 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/06 16:49:34 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmp_without_equal(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n - 1) && (s1[i] || s2[i]) && (s1[i] != '=' || s2[i] != '='))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	cmp_env(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (str1[i] > str2[i])
		return (-1);
	else if (str1[i] == str2[i])
	{
		while ((str1[i] == str2[i]) && (str1[i] != '=' || str2[i] != '='))
		{
			if (str1[i] > str2[i])
				return (-1);
			else if (str1[i] < str2[i])
				return (1);
			else
				i++;
		}
	}
	return (1);
}

int theres_eq(char *str)
{
	if(str && str[ft_strlen(str) - 1] == '=')
		return(1);
	return(0);
}

int	cmp(char	*av)
{
	int		i;
	int		j;
	char	*tmp;
	char	**arr;

	if (ft_strchr_int(av, '=') == 1)
	{
		arr = ft_split(av, '='); // possible leak
		tmp = ft_strjoin(arr[0], "="); // leak
		i = 0;
		while (g_codes.g_env[i])
		{
			if (cmp_without_equal(tmp, g_codes.g_env[i], ft_strlen(tmp)) == 0) //I think it works fine ()
			{
				g_codes.g_env[i] = ft_strdup(av);
				return (0);
			}
			i++;
		}
		if(!theres_eq(av))
			my_env(g_codes.g_env, av);
	}
	else
	{
		i = 0;
		j = 0;
		while (g_codes.g_env[i])
		{
			if (cmp_without_equal(av, g_codes.g_env[i], ft_strlen(av)) != 0)
			{
				i++;
				j++;
			}
			else
				i++;
		}
		if (i == j)
			my_env(g_codes.g_env, av);
	}
	return (0);
}



void	export(t_cmd	*data)
{
	int				i;
	char			**tmp_env;
	char			**tmp2;
	char			*tmp;

	if (data->av[1] == NULL)
	{
		tmp_env = ft_calloc(env_len(g_codes.g_env) + 1, sizeof(char *));
		if (!tmp_env)
		{
			ft_putendl_fd("ERROR !, malloc failed", 2);
			exit(1);
		}
		i = 0;
		while (g_codes.g_env[i])
		{
			tmp_env[i] = ft_strdup(g_codes.g_env[i]);
			i++;
		}
		i = 0;
		while (tmp_env[i + 1] != NULL)
		{
			if (cmp_env(tmp_env[i], tmp_env[i + 1]) == -1)
			{
				tmp = tmp_env[i];
				tmp_env[i] = tmp_env[i + 1];
				tmp_env[i + 1] = tmp;
				i = -1;
			}
			i++;
		}
		i = 0;
		while (tmp_env[i] != NULL)
		{
			tmp2 = ft_split(tmp_env[i], '=');
			if (ft_strchr_int(tmp_env[i], '=') == 1)
				printf("declare -x %s = \"%s\"\n", tmp2[0], tmp2[1]);
			else
				printf("declare -x %s\n", tmp2[0]);
			i++;
		}
	}
	else if (data->av[1] != NULL)
	{
		i = 1;
		while (data->av[i])
		{
			theres_eq(data->av[i]);
			cmp(data->av[i]);
			i++;
		}
	}
}
