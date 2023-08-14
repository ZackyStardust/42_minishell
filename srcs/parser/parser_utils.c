/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:55:10 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 19:13:40 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_match(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

void	*protect_mem(void *p)
{
	if (!p)
	{
		ft_putendl_fd("minishell: Out of memory", 2);
		exit(EXIT_FAILURE);
	}
	return (p);
}

char	*join_char(char *str, char c)
{
	char	new[2];
	char	*token;

	new[0] = c;
	new[1] = '\0';
	token = token_join(str, new, 0);
	free_str(str);
	return (token);
}

char	*exist_in_env(char	*elem, t_list *env)
{
	t_list	*cursor;

	cursor = env;
	while (cursor)
	{
		if (!ft_strncmp(elem, cursor->content, ft_strlen(elem)))
			return (cursor->content);
		cursor = cursor->next;
	}
	return (NULL);
}

int	parser_count_inquote(char *str, char c)
{
	int	ret;

	ret = 0;
	if (str[ret] && str[ret] == c && str[ret + 1] == c)
		return (0);
	while (str[ret])
	{
		if (str[ret] == c && ((str[ret + 1] == '\0')
				|| is_match(str[ret + 1], " \t\r\n\v\f<>|")))
			return (ret + 1);
		++ret;
	}
	return (1);
}
