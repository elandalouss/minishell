/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:03:19 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/16 17:41:43 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	exit_code_handler(int i)
{
	g_codes.g_error_code = i;
	g_codes.g_exit_code = i;
}

void	herdoc_utils(int status)
{
	if (WEXITSTATUS(status) == 16)
		exit(2);
	else if (WEXITSTATUS(status) == 1)
	{
		exit_code_handler(1);
		return ;
	}
}

void	herdoc_sig(pid_t id)
{
	int		status;

	signal(SIGINT, SIG_IGN);
	if (waitpid(id, &status, 0) < 0)
	{
		perror("minishell: waitpid:");
		exit_code_handler(1);
		return ;
	}
	if (WIFEXITED(status))
		herdoc_utils(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			ft_putstr_fd("\n", 2);
			exit_code_handler(1);
			return ;
		}
	}
	signal(SIGINT, handler);
}

void	heredoc_child(t_token *tokens)
{
	signal(SIGINT, SIG_DFL);
	here_docs(tokens);
}

/*ces la fonction racine de heredocs ou je cree un nouveau process***/
void	heredoc_racine(t_token	*tokens)
{
	pid_t	id;
	t_token	*temp;
	int		i;

	if (check_number(tokens) == 0)
		return ;
	id = fork();
	if (id == 0)
		heredoc_child(tokens);
	else
	{
		herdoc_sig(id);
		temp = tokens;
		i = 0;
		while (temp)
		{
			if (temp->e_type == TOKEN_DREAD)
			{
				free(temp->next->word);
				herdoc_racine_utils(i, temp);
				i++;
			}
			temp = temp->next;
		}
	}
}

void	herdoc_racine_utils(int i, t_token *temp)
{
	temp->next->word = get_file_name(i);
	temp->next->value = ft_strdup("uuuuuuuuuuuuuuuuuu");
}
