/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:59:36 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/22 13:02:40 by jchennak         ###   ########.fr       */
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


void    handler(int code);
#endif