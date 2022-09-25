/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manangement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:45:04 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/23 17:30:39 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*pour la verification des pipe error ****/
void	pipe_errors(t_token *token)
{
	if (token->next == NULL || token->prev == NULL)
	{
		ft_putstr_fd("minishell : syntax error near unexpected token `|'\n", 2);
		g_codes.g_exit_code = 258;
		g_codes.g_error_code = 1;
	}
	else if (token->next->e_type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell : syntax error near unexpected token `|'\n", 2);
		g_codes.g_exit_code = 258;
		g_codes.g_error_code = 1;
	}
}

/*pour la veriication des error de redurection*/
void	redirection_errors(t_token *token)
{
	if (!(token->next))
	{
		ft_putstr_fd
		("minishell : syntax error near unexpected token `newline' \n", 2);
		g_codes.g_exit_code = 258;
		g_codes.g_error_code = 1;
	}
	else if (token->next->e_type != TOKEN_WORD)
	{
		ft_print_error("minishell : syntax error near unexpected token `", token->next->word, "'");
		//ft_putstr_fd("MINISHELL : syntax error near unexpected token `<'\n", 2);
		g_codes.g_exit_code = 258;
		g_codes.g_error_code = 1;
	}
}

/*****pour la verification des errors pour les simple mot*/
void	word_error(t_token *token)
{
	char	*d;
	char	*s;

	d = ft_strchr(token->value, 'd');
	s = ft_strchr(token->value, 's');
	if (s && s == ft_strrchr(token->value, 's'))
	{
		ft_putstr_fd("ERROR : UNCLOSED SINGLE QUOTE \n", 2);
		g_codes.g_exit_code = 258;
		g_codes.g_error_code = 1;
	}
	if (d && d == ft_strrchr(token->value, 'd'))
	{
		ft_putstr_fd("ERROR : UNCLOSED DOUBLE QUOTE \n", 2);
		g_codes.g_exit_code = 258;
		g_codes.g_error_code = 1;
	}
}

/******la fonction racine de tout les autre fonction des error*/
void	error_management(t_data *content)
{
	t_token	*temp;

	temp = content->tokens;
	while (temp)
	{
		if (temp->e_type == TOKEN_PIPE)
			pipe_errors(temp);
		else if (temp->e_type != TOKEN_WORD)
			redirection_errors(temp);
		else
			word_error(temp);
		if (g_codes.g_error_code != 0)
			return ;
		temp = temp->next;
	}
}
