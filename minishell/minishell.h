/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:59:36 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/26 14:37:13 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "parsing/parsing.h"
#include "execution/execution.h"


// parsing commands//
typedef	struct	s_cmd t_cmd;
// {
// 	char			flag;//
// 	int				index;//
// 	int 			pipe[2];
// 	int				in_file_fd;//
// 	int				out_file_fd;//
// 	char 			**av;//
// 	char 			*cmd_path;
// 	struct s_cmd	*next;
// 	struct s_cmd	*prev;
// }	t_cmd;

t_cmd           *parsing_part(char *str);
int             execution_part(t_cmd	*data);

#endif