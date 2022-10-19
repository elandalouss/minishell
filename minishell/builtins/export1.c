/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:27:51 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/19 03:29:30 by jchennak         ###   ########.fr       */
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
	int	i;

	if (str[0] == '=')
		return (-1);
	if (str[0] == '#' || str[0] == '$')
		return (-2);
	else
	{
		if (ft_isdigit(str[0]) || (str[0] < 'a' && str[0] > 'z') \
			|| (str[0] < 'A' && str[0] > 'Z'))
			return (-1);
		i = 1;
		while (str[i] && str[i] != '=')
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (-1);
			i++;
		}
	}
	return (1);
}

int	cmp_without_equal(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n - 1) && (s1[i] || s2[i]) && (s1[i] != '=' || s2[i] != '='))
	{
		if (s1[i] != s2[i])
			break ;
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
	return (i);
}

void	free_my_env(char	*av)
{
	char	**tmp;

	tmp = g_codes.g_env;
	my_env(g_codes.g_env, av);
	free_tab(tmp);
}
