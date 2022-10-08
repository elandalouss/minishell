/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:07:20 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/08 15:45:15 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_echo_args(char *av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (av[i] == 'n')
			i++;
		else
			return (-1);
	}
	return (1);
}

void	echo_print(char **av, int i, int flag)
{
	if (av[i] != NULL)
	{
		while (av[i])
		{
			printf("%s", av[i++]);
			if (av[i])
				printf(" ");
		}
	}
	if (flag == 0)
		printf("\n");
}

void	echo(t_cmd	*data)
{
	int		i;
	char	flag;

	flag = 0;
	i = 1;
	if (!data->av[1])
	{
		printf("\n");
		return ;
	}
	while ((data->av[i] && data->av[i][0] == '-') && data->av[i][1] != '\0')
	{
		if (check_echo_args(data->av[i]) == 1)
		{
			flag = 1;
			i++;
		}
		else
			break ;
	}
	echo_print(data->av, i, flag);
}
