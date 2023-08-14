/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:29:07 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 14:47:27 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree	*parser_main(char *str, t_list *env)
{
	t_tree	*tree;
	char	*token;
	int		reset;
	int		token_type;

	reset = 1;
	tree = NULL;
	while (1)
	{
		token = parser_get_token(str, reset);
		if (syntax_error(tree, token))
		{
			get()->exit_status = 2;
			return (NULL);
		}
		if (!token)
			break ;
		token_type = parser_get_id(token);
		if (token_type == E_WORD)
			token = token_treat(token, env);
		tree_make(token, token_type, &tree);
		reset = 0;
	}
	return (tree);
}

int	parser_get_id(char *token)
{
	int	len;

	len = (int)ft_strlen(token);
	if (len == 1)
	{
		if (token[0] == '<')
			return (E_IN);
		else if (token[0] == '>')
			return (E_OUT);
		else if (token[0] == '|')
			return (E_PIPE);
	}
	else if (len == 2)
	{
		if (token[0] == '<' && token[1] == '<')
			return (E_HDOC);
		else if (token[0] == '>' && token[1] == '>')
			return (E_APPEND);
	}
	return (E_WORD);
}

char	*parser_get_token(char *str, int reset)
{
	static int	i = 0;
	char		*token;

	if (reset)
		i = 0;
	token = NULL;
	while (str[i])
	{
		if (is_match(str[i], OPERATORS))
			token = parser_get_operator(str, &i);
		else if (!is_match(str[i], WHITE_SPACE))
			token = parser_get_word(str, &i);
		if (token)
			return (token);
		i++;
	}
	i = 0;
	return (token);
}

char	*parser_get_operator(char *str, int *i)
{
	char	*token;
	int		size;

	if (!str || !i)
		return (0);
	size = (int)ft_strlen(str);
	if (is_match(str[*i], "<>") && *i < size - 1)
	{
		if (str[*i] == str[*i + 1])
		{
			token = ft_substr(str, *i, 2);
			*i += +2;
			return (token);
		}
	}
	token = ft_substr(str, *i, 1);
	*i += 1;
	return (token);
}

char	*parser_get_word(char *str, int *i)
{
	char	*token;
	int		size;

	if (!str || !i)
		return (0);
	size = *i;
	while (str[size])
	{
		if (str[size] && is_match(str[size], "\""))
			size += parser_count_inquote(&str[size + 1], str[size]);
		if (str[size] && is_match(str[size], "'"))
			size += parser_count_inquote(&str[size + 1], str[size]);
		if (!str[size] || is_match(str[size], " \t\r\n\v\f<>|"))
			break ;
		size++;
	}
	token = ft_substr(str, *i, size - (*i));
	*i = size;
	return (token);
}
