/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:44:20 by fpereira          #+#    #+#             */
/*   Updated: 2021/10/28 12:44:43 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		ret;
	size_t	i;
	size_t	sign;

	ret = 0;
	i = 0;
	sign = 1;
	if (!str[0] || !str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		ret = (ret * 10) + (str[i++] - 48);
	return (ret * sign);
}

/*int main()
{
    char    *str;
    str = "         a1";

    printf("ele %d\n", atoi(str));
    printf("eu  %d\n", ft_atoi(str));

}*/