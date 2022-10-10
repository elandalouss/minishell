/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:24:15 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/10 13:00:21 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	check_stat(t_cmd	*data, char	*path)
{
	struct stat	buff;

	if (stat(path, &buff) == -1)
		printt_error("minishell", data->av[0], \
			"No such file or directory", 127);
	if (S_ISDIR(buff.st_mode))
		printt_error("minishell", data->av[0], "is a directory", 126);
	else if (!S_ISDIR(buff.st_mode) && \
		data->av[0][ft_strlen(data->av[0]) - 1] == '/')
		printt_error("minishell", data->av[0], "Not a directory", 126);
}

int	buitin_exeution(t_cmd	*data)
{
	if (ft_strncmp(data->av[0], "echo", ft_strlen("echo ")) == 0)
		echo(data);
	else if (ft_strncmp(data->av[0], "cd", ft_strlen("cd ")) == 0)
		cd(data);
	else if (ft_strncmp(data->av[0], "pwd", ft_strlen("pwd ")) == 0)
		pwd();
	else if (ft_strncmp(data->av[0], "export", ft_strlen("export ")) == 0)
		export(data);
	else if (ft_strncmp(data->av[0], "unset", ft_strlen("unset ")) == 0)
		unset(data);
	else if (ft_strncmp(data->av[0], "env", ft_strlen("env ")) == 0)
		env();
	else if (ft_strncmp(data->av[0], "exit", ft_strlen("exit ")) == 0)
		exit_p(data);
	else
		return (-1);
	return (1);
}

pid_t	exec_cmd(t_cmd *data)
{
	pid_t	f_pid;
	int		i;

	i = 0;
	f_pid = fork();
	if (f_pid == -1)
	{
		ft_putendl_fd("fork(), allocation failed\n", 2);
		exit(1);
	}
	if (f_pid == 0)
	{
		if (buitin_exeution(data) == -1)
		{
			dup_files(data);
			if (ft_strchr_int(data->av[0], '/') == -1)
				get_path_split_join(data);
			else
				data->cmd_path = data->av[0];
			if (execve(data->cmd_path, data->av, g_codes.g_env) == -1)
				check_stat(data, data->cmd_path);
		}
	}
	return (f_pid);
}

int	execution_part(t_cmd	*data)
{
	int		terminal[2];
	pid_t	f_pid;

	terminal[0] = dup(0);
	terminal[1] = dup(1);
	if (g_codes.g_env != NULL)
	{
		if (data->next == NULL)
			ls_next_null(data, terminal);
		else
		{
			while (data != NULL)
			{
				f_pid = ls_next_not_null(data, terminal);
				data = data->next;
			}
			ft_wait(f_pid);
		}
	}
	else
		ft_putendl_fd("No such file or directory", 2);
	//system("leaks minishell");
	return (g_codes.g_exit_code % 255);
}
