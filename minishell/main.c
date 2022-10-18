/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:58:31 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/18 06:15:25 by jchennak         ###   ########.fr       */
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
	g_codes.g_exit_code = 1;
}

void	exit_shell(void)
{
	printf("exit\n");
	exit(g_codes.g_exit_code);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_cmd	*cmds_line;

	if (ac != 1)
		return (0);
	(void)av;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	my_env(env, NULL);
	while (1)
	{
		g_codes.g_error_code = 0;
		str = readline("minishell$ ");
		if (str == NULL)
			exit_shell();
		add_history(str);
		cmds_line = parsing_part(str);
		if (g_codes.g_error_code != 0)
			continue ;
		execution_part(cmds_line);
		ft_close_all(cmds_line);
		ft_free_cmds(&cmds_line);
	}
	return (g_codes.g_exit_code);
}
