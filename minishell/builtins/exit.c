/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:11:43 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/03 17:49:44 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi_exit(char *str)
{
	int				i;
	unsigned long	nbr;
	int				sign;

	sign = 1;
	i = 0;
	nbr = 0;

	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			nbr = nbr * 10 + str[i++] - '0';
		else
			printt_error("minishell: exit", str, "numeric argument required", 255);
		if (sign == 1 && nbr > LONG_MAX)
			printt_error("minishell: exit", str, "numeric argument required", 255);
		else if ((nbr - 1) > LONG_MAX) 
			printt_error("minishell: exit", str, "numeric argument required", 255);
		else if (nbr > ULONG_MAX)
			printt_error("minishell: exit", str, "numeric argument required", 255);
	}
	return (sign * nbr);
}

void	exit_p(t_cmd	*data)
{
	long				exit_code;

	printf("exit\n");
	if (data->av[1] && data->av[2])
	{
		printt_error1("minishell", "exit", "too many arguments", 1);
		return ;
	}
	if (data->av[1])
	{
		exit_code = ft_atoi_exit(data->av[1]);
		exit((unsigned char)exit_code);
	}
	exit(g_codes.g_exit_code);
}
