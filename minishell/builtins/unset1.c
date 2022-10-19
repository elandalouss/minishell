/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:17:35 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/19 00:18:12 by jchennak         ###   ########.fr       */
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

int	check_builtin_error(char *str)
{
	int	i;

	if (str[0] == '#' || str[0] == '$')
		return (-2);
	else
	{
		if (ft_isdigit(str[0]))
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
