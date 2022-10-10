/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:09:42 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/10 15:50:03 by jchennak         ###   ########.fr       */
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
	if (cmd->out_file_fd == -1 || cmd->in_file_fd == -1)
	{
		ft_putstr_fd("minishell: faild to open redirection files\n", 2);
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
	if (g_codes.g_error_code != 0)
		return (NULL);
	heredoc_racine(content.tokens);
	if (g_codes.g_error_code != 0)
		return (NULL);
/* ***********/
	// t_token *temps;
	// temps = content.tokens;
	// while (temps)
	// {
	// 	printf("old word %s\n", temps->old_word);
	// 	printf("new word %s\n", temps->word);
	// 	temps = temps->next;
	// }
/* ***********/
	removing_qoutes_and_expand(content.tokens);
	if (g_codes.g_error_code != 0)
		return (NULL);
//	printf("========================\n");
/* ***********/
	// t_token *tems;
	// tems = content.tokens;
	// while (tems)
	// {
	// 	printf("old word %s\n", tems->old_word);
	// 	printf("new word %s\n", tems->word);
	// 	tems = tems->next;
	// }
/* ***********/
	cmds_line = list_init(content.tokens);
	remplissage_cmds(cmds_line, content.tokens);
	if (g_codes.g_error_code != 0)
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
