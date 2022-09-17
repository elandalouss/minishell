/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qouted_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 06:12:42 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/17 02:14:49 by jchennak         ###   ########.fr       */
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
// void	rm_all_qoutes(t_token *token)
// {
// 	//printf("token is %s\n", token->word);
// 	//token->new_word = ft_strdup(token->word); 
// 	//printf("new word is %s\n", token->new_word);
// 	int		i;
// 	char	*c;
// 	char	*my_word;
// 	char	*my_meta;
// 	i = 0;
// 	//c = NULL;
// 	my_word = ft_strdup("");
// 	my_meta= ft_strdup("");
// 	while (token->value[i])
// 	{
// 		if (token->value[i] != 'd' && token->value[i] != 's')
// 		{
// 			c = ft_strdup(".");
// 			c[0] = token->word[i];
// 			my_word = ft_extrajoin(my_word, c, FREE_ALL);
// 			c = ft_strdup(".");
// 			c[0] = token->value[i]; // n'oubier pad de dup c :)
// 			my_meta = ft_extrajoin(my_meta, c, FREE_ALL); // dub aussi your meta :P
// 			//system ("leaks minishell");                    
// 		}
// 		i++;
// 	}
// 	token->word = my_word;
// 	//free(token->value);
// 	token->value = my_meta;
// 	//free(my_meta);
// 	//free(my_word);
// 	//printf("----new word is %s\n", token->new_word);

// }

// void remove_qoutes(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		if (ft_strchr(tokens->value, 's') || ft_strchr(tokens->value, 'd'))
// 			rm_all_qoutes(tokens);
// 			//printf("yes i haave qoute in [%s]\n", tokens->word);
// 		tokens = tokens->next;
// 	}
// }
// void	to_expand(char	*meta, char	*word, char *i)
// {
// 	if (i[1] == 'u')
// 		expand ()
// }
// char	*normal_expand(char	*str, char *meta, char c)
// {
// 	char	*prefix;
// 	char	*suffix;
// 	char	*word;
// 	int		i;
// 	char	flag;
// 	flag = 0;
// 	prefix = NULL;
// 	suffix = NULL;
// 	i = position(meta, c);
// 	if (str[i] == '\0')
// 		return (ft_substr(str, 0, ft_strlen(str) + 1));
// 	if (i > 0)
// 		prefix = ft_substr(str, 0, i);
// 	word = ft_strdup("");
// 	if (str[i] && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
// 	{
// 		suffix = ft_strdup(" ");
// 		i++;
// 		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 		{
// 			*suffix = str[i];
// 			word = ft_extrajoin(word, suffix, 1);
// 			i++;
// 		}
// 		free(suffix);
// 		flag = 1;
// 	}
// 	else
// 	{
// 		prefix = ft_extrajoin(prefix, "$", 1);
// 		suffix = normal_expand(str + (i + 1), meta + (i + 1), c);
// 	}
// 	if (flag)
// 		suffix = normal_expand(str + i, meta + i, c);
// 	word = check_word_in_env(word);
// 	if (!prefix)
// 		prefix = ft_strdup("");
// 	if (!suffix)
// 		suffix = ft_strdup("");
// 	if (!word)
// 		word = ft_strdup("");
// 	word = ft_extrajoin(prefix, word, 3);
// 	word = ft_extrajoin(word, suffix, 3);
// 	return (word);
// }
// void	expand_str(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		//printf("++++++++++++++++++++++++++++++word is %s his meta is %s token is %d\n", tokens->word, tokens->value, tokens->e_type);
// 		tokens->old_word = tokens->word;
// 		tokens->word = normal_expand(tokens->word, tokens->value, 'x');
// 		printf("to exppand word is %s his meta is %s token is %d\n", tokens->old_word, tokens->value, tokens->e_type);//expand_2();
// 		printf("%s\n", tokens->word);
// 		tokens = tokens->next;
// 	}
// }
// void    qouted_and_expand(t_token *tokens)
// {
// 	//printf("hi");
//     remove_qoutes(tokens);
// 	expand_str(tokens);
// }
// void	removing_qoutes_and_expand(ccontent)
// {
// 	;
// }
// char	*to_expand(char	*str, int *i)
// {
// 	char	*word;
// 	int		j;
// 	int		l;
// 	j = *i;
// 	j++;
// 	l = *i;
// 	while (str[j] && (ft_isalnum(str[(j)]) || str[(j)] == '_'))
// 	{
// 		j++;
// 		(*i)++;
// 	}
// 	//printf("%s str\n", str);
// //	printf("%d my j\n", j);
// //	printf("%d my i\n", *i);
// //	printf("%d my L\n", l);
// 	*i
// 	if (j == 0)
// 		return ("$");
// 	else
// 	{
// 		//if(str[j] == '"' || str[j] == '\'')
// 		//	j--;
// 		word = ft_substr(str, l + 1, j - 1);
// 		printf("my word [%s]=====\n", word);
// 		word = check_word_in_env(word);
// 		if (word)
// 			return (word);
// 	}
// 	return (NULL);
// }

char *to_expand(char *str, int *i)
{
	char 	*word;
	char	*c;
	
	word = ft_strdup("");
	(*i)++;
	while (str[(*i)] && (str[(*i)] == '_' || ft_isalnum(str[(*i)])))
	{
		c = ft_strdup(" ");
		c[0] = str[(*i)];
		word = ft_extrajoin(word, c, FREE_ALL);
		(*i)++;
	}
	(*i)--;
	word = check_word_in_env(word);
	if (word && word[0] == '\0')
	{
		free (word);
		word = NULL;
	}
	return (word);
}

int	ft_charset_chr(char	*s1, char	*charset)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_strchr(charset, s1[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	expander(t_token	*t)
{
	int		i;
	char	*c;
	char	*m;
	char	*m_helper;

	i = 0;
	t->old_word = ft_strdup(t->word);
	free (t->word);
	t->word = NULL;
	m_helper = NULL;
	while(t->value[i])
	{
		if (t->value[i] == 'x')
		{
			c = to_expand(t->old_word, &i);
			m = NULL;
			if (c)
			{
				m = ft_strdup(c);
				ft_memset(m, t->value[i], ft_strlen(m));
			}
		}
		else if (t->value[i] != 'd' && t->value[i] != 's')
		{
			c = ft_strdup(" ");
			c[0] = t->old_word[i];
			m = ft_strdup(" ");
			m[0] = t->value[i];
		}
		else
		{
			i++;
			continue ;
		}
		// printf("---%s\n---%s\n", c, m);
		// printf("---%s\n---%s\n", t->word, m_helper);
		t->word = ft_extrajoin(t->word, c, FREE_ALL);
		m_helper = ft_extrajoin(m_helper, m, FREE_ALL);
		// printf("---%s\n---%s\n", t->word, m_helper);
		i++;
	}
	free (t->value);
	t->value = m_helper;
}


void	removing_qoutes_and_expand(t_token	*tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		//printf(" in removing part %s\nthis is it's meta %s\n", tokens->word, tokens->value);
		if(ft_strchr(tokens->value, 'x'))
			expander(tokens);
		else
			tokens->old_word = ft_strdup(tokens->word);
		if (tokens->word == NULL || (ft_charset_chr(tokens->word, " \t\n") >= 0
			&& tokens->value[ft_charset_chr(tokens->word, " \t\n")] == 'u'))
			tokens->e_type = TOKEN_RDIR_AMBIGU;
		//printf(" in removing part %s\nthis is it's meta %s\nthis is its type%d\n", tokens->word, tokens->value, tokens->e_type);
		tokens = tokens->next;
	}
//	printf("%s word===\n", word);
}
