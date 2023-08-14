/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:57:44 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 15:06:23 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_last_cmd(int pid)
{
	int	status;

	main_call_sigact(SI_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		get()->exit_status = 128 + status;
		if (get()->exit_status == 130)
			ft_putchar_fd('\n', STDOUT_FILENO);
		else if (get()->exit_status > 130)
		{
			ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
			get()->exit_status = 131;
		}
	}
}

void	wait_missing_cmds(int n_cmds)
{
	int	status;

	n_cmds--;
	while (n_cmds)
	{
		wait(&status);
		n_cmds--;
	}
}

void	wait_cmds(int last_pid, int n_cmds)
{
	wait_last_cmd(last_pid);
	wait_missing_cmds(n_cmds);
}
