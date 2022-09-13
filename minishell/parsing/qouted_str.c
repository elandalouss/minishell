/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qouted_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 06:12:42 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/13 15:25:51 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*qt(char	*word, int i)
// {
// 	char	*prefix;
// //	char	*suffix;

	
// 	printf("in qt we have %s\n", word);
// 	printf("%d\n", i);
// 	// prefix = ft_strdup("");
// 	// if (i > 0)
// 	prefix = ft_substr(word, 0, i);
// 	printf("prefix %s\n", prefix);
// 	word = ft_extrajoin(prefix, &word[i], 1);
// 	return (word);
// }

// char	*remove_qt(char	*meta, char	*word)
// {
//     int i;

//     i = 0;
	
//     while(meta[i])
//     {
//         if (meta[i] == 'd' || meta[i] == 's')
//             word = qt(word, i);
//         i++;
//     }
// 	return (word);
// }


// void    remove_qoutes(t_token *tokens)
// {
// //	t_token *temp;

// //	temp = tokens;
//     while (tokens)
//     {
// 	//	printf("first boucle\n");
//         if(!ft_strchr(tokens->value, 's') || !ft_strchr(tokens->value, 'd'))
// 		{
// 			//tokens->new_word = ft_strdup(tokens->word);
//             tokens->new_word = remove_qt(tokens->value, tokens->word);
// 		}
//         tokens = tokens->next;
//     }
	
// 	// tokens = temp;
// 	// while (tokens)
// 	// {
// 	// 	printf("%s+++++new word\n",tokens->new_word);
// 	// 	tokens=tokens->next;
// 	// }
// 	// printf("-----------------\n");
// }

/*pour supprimer tout les qoutes dans une seul string***/
void	rm_all_qoutes(t_token *token)
{
	//printf("token is %s\n", token->word);
	//token->new_word = ft_strdup(token->word); 
	//printf("new word is %s\n", token->new_word);
	int		i;
	char	*c;
	char	*my_word;
	char	*my_meta;
	i = 0;
	
	//c = NULL;
	my_word = ft_strdup("");
	my_meta= ft_strdup("");
	while (token->value[i])
	{
		if (token->value[i] != 'd' && token->value[i] != 's')
		{
			c = ft_strdup(".");
			c[0] = token->word[i];
			my_word = ft_extrajoin(my_word, c, 3);
			c = ft_strdup(".");
			c[0] = token->value[i]; // n'oubier pad de dup c :)
			my_meta = ft_extrajoin(my_meta, c, 3); // dub aussi your meta :P
			//system ("leaks minishell");                    
		}
		i++;
	}
	token->word = my_word;
	//free(token->value);
	token->value = my_meta;
	//free(my_meta);
	//free(my_word);
	//printf("----new word is %s\n", token->new_word);

}


void remove_qoutes(t_token *tokens)
{
	while (tokens)
	{
		if (ft_strchr(tokens->value, 's') || ft_strchr(tokens->value, 'd'))
			rm_all_qoutes(tokens);
			//printf("yes i haave qoute in [%s]\n", tokens->word);
		tokens = tokens->next;
	}
}



void	expand_str(t_token *tokens)
{
	while (tokens)
	{
		//printf("++++++++++++++++++++++++++++++word is %s his meta is %s token is %d\n", tokens->word, tokens->value, tokens->e_type);
		if (ft_strchr(tokens->value, 'x'))
			to_expand()
			//printf("to exppand word is %s his meta is %s token is %d\n", tokens->word, tokens->value, tokens->e_type);//expand_2();
		tokens = tokens->next;
	}
}

void    qouted_and_expand(t_token *tokens)
{
	//printf("hi");
    remove_qoutes(tokens);
	expand_str(tokens);
}