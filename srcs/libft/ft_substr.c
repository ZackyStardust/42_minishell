/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 12:17:45 by fpereira          #+#    #+#             */
/*   Updated: 2021/10/23 15:38:57 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ret;
	size_t		i;
	size_t		mal;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		ret = malloc(1);
		ret[0] = '\0';
		return (ret);
	}
	mal = ft_strlen(s) - start;
	if (len > mal)
		ret = (char *)malloc(mal + 1);
	else
		ret = (char *)malloc(len + 1);
	if (!ret)
		return (0);
	i = 0;
	while (start < ft_strlen(s) && i < len)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}
