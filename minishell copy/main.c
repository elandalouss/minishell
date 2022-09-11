/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:58:31 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/09 15:44:16 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	
	if (ac != 1)
		return (0);
	(void)av;
	g_codes.g_exit_code = 0;
	my_env(env, NULL);
	while (1)
	{
		g_codes.g_error_code = 0;
		str = readline("minishell$ ");
		if (str == NULL)
		{
			printf("exit\n");
			exit(0);/*i need to exit with the last exit code */
		}
		add_history(str);
		parsing_part(str);
		if (g_codes.g_error_code != 0)
			continue ;
		printf("je suis entrain d'excuter :P\n");
	}
	return (0);
}
