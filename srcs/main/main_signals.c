/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:32:29 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/11 16:03:18 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	main_set_termios(struct termios *term, struct termios *termbase)
{
	if (tcgetattr(STDIN_FILENO, term) != 0)
	{
		ft_putstr_fd("\001\e[1m\e[35m\002" "MiniShell$ " "\001\e[1m\e[33m\002",
			STDERR_FILENO);
		perror("attributes setting failed");
		if (get()->env)
			free_env(get()->env);
		exit(1);
	}
	if (tcgetattr(STDIN_FILENO, termbase) != 0)
	{
		ft_putstr_fd("\001\e[1m\e[35m\002" "MiniShell$ " "\001\e[1m\e[33m\002",
			STDERR_FILENO);
		perror("attributes setting failed");
		if (get()->env)
			free_env(get()->env);
		exit(1);
	}
	term->c_cc[VQUIT] = _POSIX_VDISABLE;
	term->c_lflag &= ~ECHOCTL;
}

char	*main_rdl_signals(struct termios *term, struct termios *termbase)
{
	char	*str;

	main_call_sigact(SI_RLINE);
	main_attr_setting(term);
	str = readline("\001\e[1m\e[35m\002" "MiniShell$ " "\001\e[1m\e[33m\002");
	if (!str)
	{
		main_attr_setting(termbase);
		free_str(str);
		free_env(get()->env);
		ft_putendl_fd("exit", 2);
		exit(get()->exit_status);
	}
	main_call_sigact(SI_IGN);
	main_attr_setting(termbase);
	return (str);
}

void	main_handle_ctrlc(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		get()->exit_status = 130;
	}
}

void	main_heredoc_file(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGINT)
	{
		get()->exit_status = 130;
		close(STDIN_FILENO);
		write(STDOUT_FILENO, "> \n", 3);
	}
}

void	main_get_signal(struct sigaction *act, char si_mode)
{
	ft_memset(act, '\0', sizeof(*act));
	act->sa_flags = SA_SIGINFO;
	sigemptyset(&act->sa_mask);
	if (si_mode == SI_IGN)
		(act->sa_handler) = SIG_IGN;
	else if (si_mode == SI_HDOC)
		(act->sa_sigaction) = main_heredoc_file;
	else if (si_mode == SI_RLINE)
		(act->sa_sigaction) = main_handle_ctrlc;
	else if (si_mode == SI_DFL)
		(act->sa_handler) = SIG_DFL;
	else
		return ;
}
