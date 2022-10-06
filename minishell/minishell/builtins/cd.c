/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 06:39:22 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/03 17:18:04 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_cmd	*data)
{
	int		dir;

	dir = chdir(data->av[1]);
	if (dir != 0)
		printt_error1("./minishell", "cd", \
			"with only a relative or absolute path", 1);
}
