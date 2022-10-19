/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:59:36 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/19 01:56:08 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "parsing/parsing.h"
# include "execution/execution.h"

typedef struct s_cmd	t_cmd;

t_cmd		*parsing_part(char *str);
int			execution_part(t_cmd	*data);

#endif