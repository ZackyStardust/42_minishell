/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:32:37 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 17:28:24 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*exist_env_var(t_list *env, char *var_name)
{
	t_list	*cursor;
	int		size;

	if (!var_name || !env)
		return (0);
	cursor = env;
	size = ft_strlen(var_name);
	while (cursor)
	{
		if (!ft_strccmp(var_name, cursor->content, size))
			return (cursor);
		cursor = cursor->next;
	}
	return (NULL);
}

char	*expand_var(char *s, char *token, int *i, t_list *env)
{
	int		expansion_size;

	expansion_size = exp_var_size(&s[*i + 1]);
	if (!expansion_size)
		token = join_char(token, s[*i]);
	else
		token = expand_var_else(s, token, i, env);
	return (token);
}

char	*expand_var_else(char *s, char *token, int *i, t_list *env)
{
	char	*var_name;
	t_list	*cursor;
	char	*temp;
	int		expansion_size;

	expansion_size = exp_var_size(&s[*i + 1]);
	var_name = ft_substr(&s[*i + 1], 0, expansion_size);
	cursor = exist_env_var(env, var_name);
	if (cursor && cursor->content)
	{
		temp = ft_strchr(cursor->content, '=');
		if (temp)
			token = token_join(token, ft_substr(temp, 1, \
			ft_strlen(temp)), 1);
	}
	else
	{
		free_str(var_name);
		*i += expansion_size;
		return (ft_strdup(""));
	}
	free_str(var_name);
	*i += expansion_size;
	return (token);
}

char	*expand_str(char *s, t_list *env)
{
	char	*token;

	(void)env;
	token = NULL;
	token = expand_str_loop(0, s, 0, token);
	free_str (s);
	return (token);
}

char	*expand_str_loop(int size, char *s, int i, char *token)
{
	while (s[i])
	{
		if (s[i] != '$')
		{
			size = exp_word_size(s);
			token = token_join(token, ft_substr(&s[i], 0, size), 1);
			i += size - 1;
		}
		else if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
		{
			token = token_join(token, ft_itoa(get()->exit_status), 1);
			i++;
		}
		else if (s[i] == '$' && (!s[i + 1] || (s[i + 1] && s[i + 1] == '$')))
		{
			token = token_join(token, ft_strdup(" "), 1);
			break ;
		}
		else if (s[i] == '$' && s[i + 1] && s[i + 1] != '$')
			token = expand_var(s, token, &i, (get())->env);
		i++;
	}
	return (token);
}
