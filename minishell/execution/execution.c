/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:24:15 by aelandal          #+#    #+#             */
/*   Updated: 2022/09/29 17:49:29 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	check_stat(t_cmd	*data, char  *path)
{
	struct stat buff;

	if (stat(path, &buff) == -1)
		printt_error("minishell", data->av[0], "No such file or directory", 127);
	if (S_ISDIR(buff.st_mode))
		printt_error("minishell", data->av[0], "is a directory", 126);
	else
		printt_error("minishell", data->av[0], "Not a directory", 126);
}

void	dup_stdin(t_cmd	*data)
{
	if (data->flag == 1 && data->in_file_fd == -2 && data->prev != NULL)
	{
		close (data->prev->pipe[1]);
		dup2(data->prev->pipe[0], 0);
	}
	else if (data->flag == 1 && data->in_file_fd != 0)
		dup2(data->in_file_fd, 0);
}

void	dup_stdout(t_cmd	*data)
{
	if (data->flag == 1 && data->out_file_fd == -2  && data->next != NULL)
	{
		close (data->pipe[0]);
		dup2(data->pipe[1], 1);
	}
	else if (data->flag == 1 && data->out_file_fd != 1)
		dup2(data->out_file_fd, 1);
}
 
void 	reset_std(int	*terminal)
{
	dup2(terminal[0], 0);
	dup2(terminal[1], 1);
}

void	dup_files(t_cmd	*data)
{
	dup_stdin(data);
	dup_stdout(data);
}

pid_t	exec_cmd(t_cmd *data)
{
	pid_t	f_pid;
	int		i;
	char	**arr;
	
	i = 0;
	f_pid = fork();
	if (f_pid == -1)
	{
		ft_putendl_fd("fork(), allocation failed\n", 2);
		exit(-1);
	}
	if (f_pid == 0)
	{
		printf("hello1\n");
		dup_files(data);
		printf("hello2\n");
		if (ft_strchr_int(data->av[0], '/') == -1)
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
			data->cmd_path = arr[i];
			if (!data->cmd_path)
				printt_error("minishell", data->av[0], "command not found", 127);
		}
		else
			data->cmd_path = data->av[0];
		if (execve(data->cmd_path, data->av, g_codes.g_env) == -1)
			check_stat(data, data->cmd_path);
			//printt_error("minishell", data->av[0], "No such file or directory", 127);
	}
	return (f_pid);
}

void ft_wait(pid_t	f_pid)
{
	int waitpid_value;
	int	exit_status;
	
	while (1)
	{
		if ((waitpid_value = waitpid(-1, &exit_status, 0)) == -1)
			break;
		if (waitpid_value == f_pid)
		{
			if (WIFEXITED(exit_status))
			{	
				if (WIFEXITED(exit_status))
					g_codes.g_exit_code = WEXITSTATUS(exit_status);
			}
			else
			{
				if (WIFSIGNALED(exit_status))
					g_codes.g_exit_code = 128 + WTERMSIG(exit_status);
			}
		}
	}
}

int	one_cmd(t_cmd	*data)
{
	pid_t	f_pid;
	
	f_pid = exec_cmd(data);
	ft_wait(f_pid);
	return (g_codes.g_exit_code % 255);
}

int	buitin_exeution(t_cmd	*data)
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
	else
		return (-1);
	return (1);
}

pid_t	multi_pipes(t_cmd	*data)
{
	int		i;
	pid_t	f_pid;
	
	i = 0;
	if (data->next != NULL && pipe(data->pipe) == -1)
	{
		ft_putendl_fd("ERROR!, pipe failed", 2);
		exit(-1);
	}
	f_pid = exec_cmd(data);
	return (f_pid);
}


int    execution_part(t_cmd  *data)
{
	int		terminal[2];
	pid_t	f_pid;

	terminal[0] = dup(0);
	terminal[1] = dup(1);
	if (data->next == NULL && data->flag == 1)
	{
		dup_files(data);
		if (buitin_exeution(data) == -1)
			one_cmd(data);
		reset_std(terminal);
	}
	else
	{
		while (data != NULL)
		{
			f_pid = multi_pipes(data);
			reset_std(terminal);
			if (data->next != NULL)
				close(data->pipe[1]);
			if (data->prev != NULL)
				close (data->prev->pipe[0]);
			data = data->next;
		}
		ft_wait(f_pid);
	}
	return (g_codes.g_exit_code % 255);
}
