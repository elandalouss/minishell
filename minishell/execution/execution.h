/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:23:24 by aelandal          #+#    #+#             */
/*   Updated: 2022/09/29 16:20:48 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "../minishell.h"
# include "../parsing/parsing.h"
# include <sys/wait.h>
# include <sys/stat.h>

typedef	struct	s_cmd
{
	char			flag;//
	int				index;//
	int 			pipe[2];
	int				in_file_fd;//
	int				out_file_fd;//
	char 			**av;//
	char 			*cmd_path;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

int     lst_size(t_cmd  *data);
void    free_2d(char **arr_2d, int ind);
int     ft_strchr_int(const char *s, int c);
void	printt_error(const char *str1, const char *str2, const char *str3, int error_code);
//builtin
void    unset(t_cmd *data);
void	echo(t_cmd	*data);
void    cd(t_cmd	*data);
void    env();
void    pwd();
void    exit_p();
# endif
