/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:58:31 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/12 00:33:06 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int code)
{
	(void)code;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_cmd	*cmds_line;

	if (ac != 1)
		return (0);
	(void)av;
	g_codes.g_exit_code = 0;
	signal(SIGINT, handler);// signal ctl + c // to see
	signal(SIGQUIT, SIG_IGN);// ctrl + "\" // to see
	my_env(env, NULL);
	while (1)
	{
		g_codes.g_error_code = 0;
		str = readline("minishell$ ");
		if (str == NULL)
		{
			printf("exit\n");
			exit(0);/*i need to exit with the last exit code */ // REGLER
		}
		add_history(str);// to see
		cmds_line = parsing_part(str);
		if (g_codes.g_error_code != 0)
			continue ;// I GUESS NO NEED TO CHECK IF CMDS_LINE IS null
		execution_part(cmds_line);
		ft_free_cmds(&cmds_line);
		system("leaks minishell");
	}
	return (0);
}
