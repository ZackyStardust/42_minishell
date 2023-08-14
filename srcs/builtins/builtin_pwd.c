/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:45:19 by gpardini          #+#    #+#             */
/*   Updated: 2023/08/13 14:36:34 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_pwd(int fd)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	if (exe()->flag == 2)
	{
		get()->exit_status = 1;
		return ;
	}
	ft_putendl_fd(cwd, fd);
	get()->exit_status = 0;
}
