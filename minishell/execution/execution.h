/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:23:24 by aelandal          #+#    #+#             */
/*   Updated: 2022/09/22 13:15:23 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "../minishell.h"
# include <sys/wait.h>

int     lst_size(t_cmd  *data);
void    free_2d(char **arr_2d, int ind);
int     ft_strchr_int(const char *s, int c);
//builtin
void    unset(t_cmd *data);
void	echo(t_cmd	*data);
void    cd(t_cmd	*data);
void    env();
void    pwd();
void    exit_p();
# endif
