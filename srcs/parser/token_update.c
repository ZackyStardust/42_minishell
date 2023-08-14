/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:11:46 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 19:21:29 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	token_get_quoted(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[0] == s[i])
			return (i + 1);
		i++;
	}
	return (0);
}

int	token_get_unquoted(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (is_match(s[i], "\'\""))
			return (i);
		++i;
	}
	return (i);
}

int	token_get_size(char *s)
{
	if (is_match(s[0], "\'\""))
		return (token_get_quoted(s));
	else
		return (token_get_unquoted(s));
}

char	*token_update(char *token, char *new_token, int *index, t_list *env)
{
	char	*str;
	int		i;
	int		size;

	i = *index;
	size = token_get_size(&token[i]);
	if (size)
	{
		if (is_match(token[i], "\'\""))
		{
			str = protect_mem(ft_substr(&token[i + 1], 0, size - 2));
			if (token[i] == '"')
				str = expand_str(str, env);
		}
		else
		{
			str = protect_mem(ft_substr(&token[i], 0, size));
			str = expand_str(str, env);
		}
		new_token = token_join(new_token, str, 1);
		*index += size - 1;
	}
	else
		new_token = join_char(new_token, token[i]);
	return (new_token);
}

char	*token_join(char *t1, char *t2, int trigger)
{
	char	*new;

	new = NULL;
	if (t1 && t2)
		new = protect_mem(ft_strjoin(t1, t2));
	else if (!t1 && t2)
		new = protect_mem(ft_strdup(t2));
	else if (t1 && !t2)
		new = protect_mem(ft_strdup(t1));
	free_str(t1);
	if (trigger || !t2)
		free_str(t2);
	return (new);
}
