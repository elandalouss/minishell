/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 05:31:48 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/20 05:34:21 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(char *av)
{
	char	**temp;

	temp = g_codes.g_env;
	my_env(g_codes.g_env, av);
	free_tab(temp);
}

void	init_tmp_struct(t_tmp	*vars, char *av)
{
	vars->arr_av = ft_split(av, '=');
	vars->arr_env = ft_split(g_codes.g_env[vars->i], '=');
	vars->join_av = ft_strjoin(vars->arr_av[0], "=");
	vars->join_env = ft_strjoin(vars->arr_env[0], "=");
}
