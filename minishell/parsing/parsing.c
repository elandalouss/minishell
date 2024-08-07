/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:09:42 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/19 01:58:14 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_file(t_token *token_r, t_token *token_w, t_cmd *cmd)
{
	if (token_r)
		cmd->in_file_fd = open(token_r->next->word, O_RDONLY);
	if (token_w && token_w->e_type == TOKEN_WRITE)
		cmd->out_file_fd = open(token_w->next->word,
				O_WRONLY | O_TRUNC);
	else if (token_w && token_w->e_type == TOKEN_DWRITE)
		cmd->out_file_fd = open(token_w->next->word,
				O_RDWR | O_APPEND);
	if (cmd->out_file_fd == -1)
	{
		perror(ft_strjoin("minishell : ", token_w->next->word));
		g_codes.g_exit_code = 1;
		g_codes.g_error_code = 1;
	}
	else if (cmd->in_file_fd == -1)
	{
		perror(ft_strjoin("minishell : ", token_r->next->word));
		g_codes.g_exit_code = 1;
		g_codes.g_error_code = 1;
	}
}

void	remplire_content(t_data *content, char *str)
{
	content->input = ft_strdup(str);
	content->meta_v = meta_data(str);
	content->tokens = to_tokeniser(*content);
}

void	check_content(t_data *content)
{
	ft_free_content(content);
	g_codes.g_error_code = 1;
}

/*la fonction racine de tout les fonction de parsing part :)  */
t_cmd	*parsing_part(char *str)
{
	t_data	content;
	t_cmd	*cmds_line;

	remplire_content(&content, str);
	if (content.tokens == NULL)
	{
		check_content(&content);
		return (NULL);
	}
	error_management(&content);
	if (check_error_code(&content) == 0)
		return (NULL);
	heredoc_racine(content.tokens);
	if (check_error_code(&content) == 0)
		return (NULL);
	removing_qoutes_and_expand(content.tokens);
	if (check_error_code(&content) == 0)
		return (NULL);
	cmds_line = list_init(content.tokens);
	remplissage_cmds(cmds_line, content.tokens);
	if (check_error_code(&content) == 0)
		return (NULL);
	ft_free_list(&content.tokens);
	ft_free_content(&content);
	return (cmds_line);
}

/*remplissage de token list :)*/
void	add_token(t_token **head, t_token *token)
{
	t_token	*tmp;

	if (head)
	{
		if (*head == NULL)
			*head = token;
		else
		{
			tmp = *head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = token;
			if (token)
				token->prev = tmp;
		}
	}
}
