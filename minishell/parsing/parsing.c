/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:09:42 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/29 17:29:12 by jchennak         ###   ########.fr       */
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

/*la fonction racine de tout les fonction de parsing part :)  */
t_cmd	*parsing_part(char *str)
{
	t_data	content;
	t_cmd	*cmds_line;

	content.input = ft_strdup(str);
	content.meta_v = meta_data(str);
	content.tokens = to_tokeniser(content);
	if (content.tokens == NULL)
	{
		ft_free_content(&content);
		g_codes.g_error_code = 1;
		return (NULL);
	}
	error_management(&content);
	if (g_codes.g_error_code != 0)
		return (NULL);// i guess u need free list and content :)
	heredoc_racine(content.tokens);
	if (g_codes.g_error_code != 0)
		return (NULL);// i guess u need free list and content :)
	removing_qoutes_and_expand(content.tokens);
	if (g_codes.g_error_code != 0)
		return (NULL);// i guess u need free list and content :)
	cmds_line = list_init(content.tokens);//function the creat the final linked list
	remplissage_cmds(cmds_line, content.tokens);
	if (g_codes.g_error_code != 0)
		return (NULL);// i guess u need free list and content :)
	ft_free_list(&content.tokens);// tu dois les retourner 
	ft_free_content(&content);// je penses que tu vas utiliser cette variable apres :)
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

/*ces la fonction racine de mon lexer :)*/
t_token	*to_tokeniser(t_data content)
{
	t_lexer	*lex;
	t_token	*token;
	t_token	*final;

	final = NULL;
	lex = init_lexer(content.input, content.meta_v);
	token = lexer_get_next_token(lex);
	add_token(&final, token);
	while (token != NULL)
	{
		token = lexer_get_next_token(lex);
		add_token(&final, token);
	}
	free(lex);
	return (final);
}


