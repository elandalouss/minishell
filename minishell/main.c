/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:58:31 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/22 08:32:15 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_cmd	*cmds_line;

	if (ac != 1)
		return (0);
	(void)av;
	g_codes.g_exit_code = 0;
	signal(SIGINT, handler);// signal ctl + c 
	signal(SIGQUIT, SIG_IGN);// ctrl + "\" 
	my_env(env, NULL);
	while (1)
	{
		g_codes.g_error_code = 0;
		str = readline("minishell$ ");
		if (str == NULL)
		{
			printf("exit\n");
			exit(0);/*i need to exit with the last exit code */ // c'est just
		}
		add_history(str);
		cmds_line = parsing_part(str);
		if (g_codes.g_error_code != 0)
			continue ;// I GUESS NO NEED TO CHECK IF CMDS_LINE IS null
		printf("je suis entrain d'excuter :P\n");
	}
	return (0);
}
