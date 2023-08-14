/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 12:14:46 by fpereira          #+#    #+#             */
/*   Updated: 2021/10/23 15:00:54 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	ii;

	if (!s1 || !set)
		return (0);
	ii = 0;
	while (s1[ii] && ft_strchr(set, s1[ii]))
		ii++;
	i = ft_strlen(&s1[ii]);
	while (i && ft_strchr(set, s1[ii + i]))
		i--;
	return (ft_substr(&s1[ii], 0, i + 1));
}
