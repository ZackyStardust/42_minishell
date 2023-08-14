/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:29:02 by fpereira          #+#    #+#             */
/*   Updated: 2023/08/13 21:08:14 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_data	*get(void)
{
	static t_data	data;

	return (&data);
}

t_exec	*exe(void)
{
	static t_exec	exe;

	return (&exe);
}

void	sighandler(int sig_num)
{
	(void)sig_num;
	signal(SIGTSTP, sighandler);
	signal(SIGINT, sighandler);
}

void	parse_and_execute(char *str)
{
	exe()->c = 1;
	(get())->tree = parser_main(str, (get())->env);
	if (!get()->tree)
		return ;
	get()->tree_head = get()->tree;
	if (get()->tree->left && !node_is_redir_main(get()->tree->left))
	{
		exe()->c++;
		while (get()->tree->left->type == E_PIPE)
		{
			get()->tree = get()->tree->left;
			exe()->c++;
		}
	}
	exe()->fd = 0;
	exe()->doc = 0;
	exe()->n_c = exe()->c;
	exe()->env = get()->env;
	exe()->flag = 0;
	executor_main(&get()->tree, exe()->c);
	free_tree(get()->tree_head);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input_str;

	(void)argc;
	(void)argv;
	input_str = NULL;
	main_set_enviroment(envp);
	main_set_termios(&get()->term, &get()->termbase);
	while (true)
	{
		input_str = main_rdl_signals(&get()->term, &get()->termbase);
		if (empty_input(input_str))
		{
			add_history(input_str);
			if (main_syntax_check(input_str))
			{
				free_str(input_str);
				continue ;
			}
		}
		parse_and_execute(input_str);
		free_str(input_str);
	}
	return (0);
}

// rosa \001\e[1m\e[35m\002
// amarelo \001\e[1m\e[33m\002
// verde 001\e[32m\002
// verde claro \001\e[1m\e[32m\002
