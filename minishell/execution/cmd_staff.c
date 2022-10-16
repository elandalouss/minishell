/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_staff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:23:31 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/10 12:58:40 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	get_path_split_join(t_cmd	*data)
{
	int		i;
	char	**arr;

	i = 0;
	if (g_codes.g_env[i])
	{
		while (g_codes.g_env[i])
		{
			if (ft_strncmp(g_codes.g_env[i], "PATH=", 5) == 0)
				break ;
			i++;
		}
		arr = ft_split(g_codes.g_env[i], ':');
		i = 0;
		while (arr[i])
		{
			arr[i] = ft_strjoin(arr[i], "/");
			arr[i] = ft_strjoin(arr[i], data->av[0]);
			if (access(arr[i], X_OK) == 0)
				break ;
			i++;
		}
		data->cmd_path = ft_strdup(arr[i]);
		free_tab(arr);
		if (!data->cmd_path)
			printt_error ("minishell", data->av[0], "command not found", 127);
	}
}

int	one_cmd(t_cmd	*data)
{
	pid_t	f_pid;

	if (data->flag == 1)
	{
		f_pid = exec_cmd(data);
		ft_wait(f_pid);
	}
	return (g_codes.g_exit_code % 255);
}

pid_t	exec_cmd_2(t_cmd *data)
{
	pid_t	f_pid;
	static int i = 0;

	i++;
	f_pid = fork();
	if (f_pid == -1)
	{
		ft_putendl_fd("fork(), allocation failed\n", 2);
		exit(1);
	}
	if (f_pid == 0)
	{
		if (data->av == NULL && data->flag == 1)
			printt_error("minishell", " ", "command not found", 127);
		dup_files(data);
		if (buitin_exeution(data) == -1)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (ft_strchr_int(data->av[0], '/') == -1)
				get_path_split_join(data);
			else
				data->cmd_path = data->av[0];
			if (execve(data->cmd_path, data->av, g_codes.g_env) == -1)
				check_stat(data, data->cmd_path);
			exit(g_codes.g_exit_code);
		}
		exit(g_codes.g_exit_code);
	}
	return (f_pid);
}

pid_t	multi_pipes(t_cmd	*data)
{
	pid_t	f_pid;

	if (data->next != NULL && pipe(data->pipe) == -1)
	{
		ft_putendl_fd("ERROR!, pipe failed", 2);
		exit(1);
	}
	if (data->flag == 1)
	{
		f_pid = 0;
		f_pid = exec_cmd_2(data);
		return (f_pid);
	}
	return (0);
}

void	ls_next_null(t_cmd *data, int *terminal)
{
	dup_files(data);
	if (buitin_exeution(data) == -1)
		one_cmd(data);
	reset_std(terminal);
}

pid_t	ls_next_not_null(t_cmd *data, int *terminal)
{
	pid_t	f_pid;

	f_pid = multi_pipes(data);
	reset_std(terminal);
	if (data->next != NULL)
		close(data->pipe[1]);
	if (data->prev != NULL)
		close (data->prev->pipe[0]);
	return (f_pid);
}
