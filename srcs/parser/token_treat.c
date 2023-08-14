/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_treat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:18:02 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 19:22:54 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*token_treat(char *token, t_list *env)
{
	char	*home;
	char	*new_token;
	int		i;

	if (!token)
		return (0);
	home = home_expand(token, env);
	if (home)
	{
		free_str (token);
		return (home);
	}
	if (!token_need_treat(token))
		return (token);
	i = 0;
	new_token = ft_calloc(1, sizeof(char));
	while (token[i])
	{
		new_token = token_update(token, new_token, &i, env);
		++i;
	}
	free_str (token);
	return (new_token);
}

int	token_need_treat(char *token)
{
	int	i;
	int	s_quote;
	int	d_quote;
	int	dollar;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	dollar = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			s_quote++;
		if (token[i] == '\"')
			d_quote++;
		if (token[i] == '$')
			dollar++;
		++i;
	}
	if (s_quote > 1 || d_quote > 1 || dollar > 0)
		return (1);
	return (0);
}
