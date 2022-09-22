/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:24:15 by aelandal          #+#    #+#             */
/*   Updated: 2022/09/22 13:16:21 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	one_cmd(t_cmd	*data)
{
	int		i;
	pid_t	f_pid;
	char	**arr;
	int		exit_status;

	i = 0;
	
	f_pid = fork();
	if (f_pid == -1)
		exit(-1); // exit incorrect xd
	if (f_pid == 0)
	{
		while (g_codes.g_env[i])
		{
			if (ft_strncmp(g_codes.g_env[i], "PATH=", 5) == 0)
				break;
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
		if (execve(arr[i], data->av, g_codes.g_env) == -1)
			exit (-1); // exit incorrect xd
	}
	else
	{
		if (waitpid(f_pid, &exit_status, 0) == -1)
			exit (-1); // exit incorrect xd
	}
}

void	buitin_exeution(t_cmd	*data)
{
	if (ft_strncmp(data->av[0], "echo", ft_strlen("echo")) == 0)
		echo(data);
	else if (ft_strncmp(data->av[0], "cd", ft_strlen("cd")) == 0)
		cd(data);
	else if (ft_strncmp(data->av[0], "pwd", ft_strlen("pwd")) == 0)
		pwd();
	else if (ft_strncmp(data->av[0], "export", ft_strlen("export")) == 0)
		;
	else if (ft_strncmp(data->av[0], "unset", ft_strlen("unset")) == 0)
		unset(data);
	else if (ft_strncmp(data->av[0], "env", ft_strlen("env")) == 0)
		env();
	else if (ft_strncmp(data->av[0], "exit", ft_strlen("exit")) == 0)
		exit_p();
}

void    execution_part(t_cmd  *data)
{
	if (data->next == NULL)
	{
		buitin_exeution(data);
		one_cmd(data);
	}
	else //multi pipes part :)
	{
		while (data != NULL)
		{
			data = data->next;
		}
	}
}