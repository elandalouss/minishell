/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_wait_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:48:56 by aelandal          #+#    #+#             */
/*   Updated: 2022/09/30 12:49:01 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
	if (data->flag == 1 && data->out_file_fd == -2 && data->next != NULL)
	{
		close (data->pipe[0]);
		dup2(data->pipe[1], 1);
	}
	else if (data->flag == 1 && data->out_file_fd != 1)
		dup2(data->out_file_fd, 1);
}

void	reset_std(int	*terminal)
{
	dup2(terminal[0], 0);
	dup2(terminal[1], 1);
}

void	dup_files(t_cmd	*data)
{
	dup_stdin(data);
	dup_stdout(data);
}

void	ft_wait(pid_t	f_pid)
{
	int	waitpid_value;
	int	exit_status;

	while (1)
	{
		waitpid_value = waitpid(-1, &exit_status, 0);
		if (waitpid_value == -1)
			break ;
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
