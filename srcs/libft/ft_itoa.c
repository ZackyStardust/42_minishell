/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:47:36 by fpereira          #+#    #+#             */
/*   Updated: 2021/10/28 13:02:36 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*changer(char *ret, long nf, int sign, int alg)
{
	if (nf == 0)
	{
		ret = (char *)malloc(2);
		if (!ret)
			return (0);
		ret[0] = '0';
		ret[1] = '\0';
		return (ret);
	}
	ret = (char *)malloc(alg + 1);
	if (!ret)
		return (0);
	if (sign)
		ret[0] = '-';
	ret[alg--] = '\0';
	while (nf > 0)
	{
		ret[alg--] = nf % 10 + '0';
		nf /= 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	long		nf;
	size_t		alg;
	int			sign;
	char		*ret;

	ret = 0;
	alg = 0;
	nf = (long)n;
	if (nf < 0)
	{
		sign = 1;
		nf *= -1;
		alg++;
		n *= -1;
	}
	while ((long)n)
	{
		n /= 10;
		alg++;
	}
	return (changer (ret, nf, sign, alg));
}
