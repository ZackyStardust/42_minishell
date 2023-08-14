/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:48:05 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 17:27:37 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exp_word_size(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '$')
			return (i);
	return (i);
}

int	exp_var_name(char c, int i)
{
	if (i == 0 && (ft_isalpha(c) || c == '_'))
		return (1);
	if (i > 0 && (ft_isalnum(c) || c == '_'))
		return (1);
	return (0);
}

int	exp_var_size(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!exp_var_name(s[i], i))
			return (i);
		++i;
	}
	return (i);
}

int	ft_strccmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (s2[n] == '=')
	{
		while (s1[i] && s2[i] && s1[i] == s2[i])
		{
			if (i < (n - 1))
				i++;
			else
				return (0);
		}
		return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	}
	return (1);
}
