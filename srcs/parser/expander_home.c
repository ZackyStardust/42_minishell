/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_home.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:02:51 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/11 16:37:15 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*home_expansion(char *token, int size, t_list *env)
{
	char	*home;
	char	*tmp;

	home = exist_in_env("HOME", env);
	if (!home)
		return (NULL);
	if (size == 1)
		home = ft_substr(home, 5, ft_strlen(home) - 4);
	else
	{
		home = protect_mem(ft_substr(home, 5, ft_strlen(home)));
		tmp = protect_mem(ft_substr(token, 1, ft_strlen(token)));
		home = ft_strjoin(home, tmp);
		free(tmp);
	}
	return (home);
}

char	*home_expand(char *token, t_list *env)
{
	int		size;
	char	*new;

	size = ft_strlen(token);
	new = NULL;
	if (!token)
		return (NULL);
	if ((size == 1 && token[0] == '~') || 
		(size == 2 && (token [0] == '~' && token[1] == '/')))
		new = home_expansion(token, size, env);
	return (new);
}
