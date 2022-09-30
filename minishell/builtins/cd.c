/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 06:39:22 by aelandal          #+#    #+#             */
/*   Updated: 2022/09/30 14:41:23 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_cmd	*data)
{
	int		dir;
	char	*tmp;

	if (!data->av[1])
		data->av[1] = ft_strdup("/Users/aelandal");
	dir = chdir(data->av[1]);
	if (dir != 0)
	{
		tmp = ft_strjoin("cd : ", data->av[1]);
		perror(tmp);
	}
}
