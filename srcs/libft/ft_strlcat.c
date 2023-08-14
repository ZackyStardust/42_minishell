/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:05:37 by fpereira          #+#    #+#             */
/*   Updated: 2021/10/19 12:20:03 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ii;

	i = 0;
	ii = 0;
	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	while (dst[i] && i < dstsize)
		i++;
	while (src[ii] && i + 1 < dstsize)
		dst[i++] = src[ii++];
	if (i < dstsize)
		dst[i] = '\0';
	while (src[ii++])
		i++;
	return (i);
}
