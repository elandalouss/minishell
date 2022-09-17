/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:50:30 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/17 03:19:29 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_list(t_token **token)
{
	t_token	*temp;

	while (*token)
	{
		temp = *token;
		*token = (*token)->next;
		free(temp->value);
		free(temp->word);
		free(temp->old_word);
		free(temp);
	}
	*token = 0;
}

void	ft_free_content(t_data *content)
{
	if (content->input)
		free(content->input);
	if(content->meta_v)
		free(content->meta_v);
}
