/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:55:32 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/12 00:45:10 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	check_export_error(char *str)
{
	if (str[0] == '#' || str[0] == '$')
		return (-2);
	else if ((str[0] < 'a' || str[0] > 'z') && (str[0] < 'A' \
		|| str[0] > 'Z') && str[0] != '_')
		return (-1);
	return (1);
}

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

int	theres_eq(char *str)
{
	if (str && str[ft_strlen(str) - 1] == '=')
		return (1);
	return (0);
}

int	cmp(char	*av)
{
	int		i;
	int		j;
	int		big_lenght;
	char	**arr_av;
	char	**arr_env;

	if (ft_strchr_int(av, '=') == 1)
	{
		arr_av = ft_split(av, '=');
		i = 0;
		while (g_codes.g_env[i])
		{

			arr_env = ft_split(g_codes.g_env[i], '=');
			if (ft_strlen(arr_av[0]) >= ft_strlen(arr_env[0]))
				big_lenght = ft_strlen(arr_av[0]);
			else
				big_lenght = ft_strlen(arr_env[0]);
			if (cmp_without_equal(arr_av[0], arr_env[0], big_lenght) == 0)
			{
				g_codes.g_env[i] = ft_strdup(av);
				return (0);
			}
			i++;
		free_tab(arr_env);
		}

		if (!theres_eq(av))
		{
			char **temp;
			temp = g_codes.g_env;
			my_env(g_codes.g_env, av);
			free_tab(temp);
		}
		free_tab(arr_av);   
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

void	export_null(char	**tmp_env)
{
	int				i;
	char			*tmp;
	char			*tmp3;
	char			**tmp2;

	if (!tmp_env)
	{
		ft_putendl_fd("ERROR !, malloc failed", 2);
		exit(1);
	}
	i = 0;
	while (g_codes.g_env[i])
	{
		free(tmp_env[i]);
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
		{
			tmp3 = ft_substr(tmp_env[i], \
				ft_strlen(tmp2[0]) + 1, ft_strlen(tmp_env[i]));
			printf("declare -x %s=\"%s\"\n", tmp2[0], tmp3);
			free(tmp3);
		}
		else
			printf("declare -x %s\n", tmp2[0]);
		i++;
		free_tab(tmp2);
	}
	free_tab(tmp_env);
}

void	export(t_cmd	*data)
{
	int				i;
	char			**tmp_env;

	tmp_env = ft_calloc(env_len(g_codes.g_env) + 1, sizeof(char *));
	if (data->av[1] == NULL)
		export_null(tmp_env);
	else if (data->av[1] != NULL)
	{
		i = 1;
		while (data->av[i])
		{
			theres_eq(data->av[i]);
			if (check_export_error(data->av[i]) == -2)
			{
				export_null(tmp_env);
				return ;
			}
			else if (check_export_error(data->av[i]) == -1)
			{
				printt_error1("./minishell: export", data->av[i], \
					"not a valid identifier", 1);
			}
			cmp(data->av[i]);
			i++;
		}
	}
}
