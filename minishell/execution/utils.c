/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 06:02:30 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/18 06:03:01 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	find_right_path(t_cmd	*data, char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		arr[i] = ft_strjoin(arr[i], "/");
		arr[i] = ft_strjoin(arr[i], data->av[0]);
		if (access(arr[i], X_OK) == 0)
			break ;
		i++;
	}
	data->cmd_path = ft_strdup(arr[i]);
	free_tab(arr);
}

void	get_path_split_join(t_cmd	*data)
{
	int		i;
	char	**arr;

	i = 0;
	if (g_codes.g_env[i])
	{
		while (g_codes.g_env[i])
		{	
			if (ft_strncmp(g_codes.g_env[i], "PATH=", 5) == 0)
				break ;
			i++;
		}
		arr = ft_split(g_codes.g_env[i], ':');
		if (!arr)
			printt_error("minishell", data->av[0], \
				"No such file or directory", 127);
		find_right_path(data, arr);
		if (!data->cmd_path)
			printt_error ("minishell", data->av[0], "command not found", 127);
	}
}
