/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:07:34 by fpereira          #+#    #+#             */
/*   Updated: 2021/10/23 15:53:34 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (needle[0] == 0)
		return ((char *)haystack);
	if (!haystack && !len)
		return (NULL);
	while (i < len && haystack[i])
	{
		if (len - i >= ft_strlen(needle))
			if (haystack[i] == *needle)
				if (!ft_strncmp(haystack + i, needle, ft_strlen(needle)))
					return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
