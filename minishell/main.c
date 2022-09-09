/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:58:31 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/08 19:07:45 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;

	g_codes.g_exit_code = 0;
	while (1)
	{
		g_codes.g_error_code = 0;
		str = readline("minishell$ ");
		if (str == NULL)
			exit(0);/*i need to exit with the last exit code */
		add_history(str);
		parsing_part(str);
		if (g_codes.g_error_code != 0)
			continue ;
		printf("je suis entrain d'excuter :P\n");
	}
	return (0);
}
