/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:37:30 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/11 16:02:18 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	main_call_sigact(char act_choice)
{
	struct sigaction	act;

	main_get_signal(&act, act_choice);
	if (sigaction(SIGQUIT, &act, NULL) == -1
		|| sigaction(SIGINT, &act, NULL) == -1)
	{
		ft_putstr_fd
		("\001\e[1m\e[35m\002" "MiniShell$ " "\001\e[1m\e[33m\002",
		STDERR_FILENO);
		perror("fatal");
		if (get()->env)
			free_env(get()->env);
		exit(1);
	}
}

void	main_attr_setting(struct termios *term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) != 0)
	{
		ft_putstr_fd("\001\e[1m\e[35m\002" "MiniShell$ " "\001\e[1m\e[33m\002",
			STDERR_FILENO);
		perror("attributes setting failed");
		if (get()->env)
			free_env(get()->env);
		exit(1);
	}
}
