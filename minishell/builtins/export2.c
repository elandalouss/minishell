/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:29:00 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/19 05:18:09 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	theres_eq(char *str)
{
	if (str && str[ft_strlen(str) - 1] == '=')
		return (1);
	return (0);
}

void	free_env(char *av)
{
	char	**temp;

	if (theres_eq(av))
	{
		temp = g_codes.g_env;
		my_env(g_codes.g_env, av);
		free_tab(temp);
	}		
}

void	add_env(char *av)
{
	int		i;
	int		big_lenght;
	char	**arr_env;
	char	**arr_av;

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
			free(g_codes.g_env[i]);
			g_codes.g_env[i] = ft_strdup(av);
			return ;
		}
		free_tab(arr_env);
		i++;
	}
	free_env(av);
	free_tab(arr_av);
}

int	cmp(char	*av)
{
	int		i;
	int		j;

	if (ft_strchr_int(av, '=') == 1)
		add_env(av);
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
			{
			printf("%s====%s\n", av, g_codes.g_env[i]);
				i++;

			}
		}
		if (i == j)
			free_my_env(av);
	}

	return (0);
}

void	cmp_str_env(char **tmp_env)
{
	int		i;
	char	*tmp;

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

}
