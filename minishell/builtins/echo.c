/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:07:20 by aelandal          #+#    #+#             */
/*   Updated: 2022/09/23 15:23:10 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_echo_args(char *av)
{
	int i = 1;
	while (av[i])
	{
		if (av[i] == 'n')
			i++;
		else
			return (-1);
	}
	return (1);
}

void	echo(t_cmd	*data)
{
	int		i = 1;
	char	flag = 0;
	if (!data->av[1])
	{
		printf("\n");
		return ;
	}
	while (data->av[i] && data->av[i][0] == '-')
	{
		if (check_echo_args(data->av[i]) == 1)
		{
			flag = 1;
			i++;
		}
		else
			break ;
	}
	if (data->av[i] != NULL)
	{
		while (data->av[i])
		{
			printf("%s", data->av[i++]);
			if (data->av[i])
				printf(" ");
		}
	}
	if (flag == 0)
		printf("\n");
}
