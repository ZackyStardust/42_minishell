/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_frees2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:41:08 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 14:43:13 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	list_clear(t_list *env)
{
	if (!env)
		return ;
	if (env && env->next)
		list_clear(env->next);
	free(env->content);
	free(env);
	env = NULL;
}
