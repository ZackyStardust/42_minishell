/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:23:09 by fpereira          #+#    #+#             */
/*   Updated: 2021/10/26 17:16:05 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newl;
	t_list	*newe;

	if (!lst)
		return (0);
	newl = 0;
	while (lst)
	{
		newe = ft_lstnew(f(lst->content));
		if (!newe)
		{
			ft_lstclear(&newl, del);
			return (0);
		}
		ft_lstadd_back(&newl, newe);
		lst = lst->next;
	}
	return (newl);
}
