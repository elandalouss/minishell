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

void	exit_p(t_cmd	*data)
{
	int	exit_code;

	if (data->av[1])
	{
		exit_code = ft_atoi(data->av[1]);
		exit(exit_code);
	}
	exit(g_codes.g_exit_code);
}
