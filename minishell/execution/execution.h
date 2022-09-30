/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:23:24 by aelandal          #+#    #+#             */
/*   Updated: 2022/09/30 14:30:33 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "../minishell.h"
# include "../parsing/parsing.h"
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_cmd
{
	char			flag;
	int				index;
	int				pipe[2];
	int				in_file_fd;
	int				out_file_fd;
	char			**av;
	char			*cmd_path;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

int		lst_size(t_cmd	*data);
void	dup_stdin(t_cmd	*data);
void	dup_stdout(t_cmd	*data);
void	dup_files(t_cmd	*data);
void	reset_std(int	*terminal);
void	free_2d(char **arr_2d, int ind);
int		ft_strchr_int(const char *s, int c);
void	printt_error(char *str1, char *str2, char *str3, int error_code);
int		buitin_exeution(t_cmd	*data);
void	ls_next_null(t_cmd *data, int *terminal);
pid_t	ls_next_not_null(t_cmd *data, int *terminal);
int		one_cmd(t_cmd	*data);
pid_t	exec_cmd(t_cmd *data);
void	get_path_split_join(t_cmd	*data);
void	ft_wait(pid_t	f_pid);
void	unset(t_cmd *data);
void	echo(t_cmd	*data);
void	cd(t_cmd	*data);
void	env(void);
void	pwd(void);
void	exit_p(void);

#endif
