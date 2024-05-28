/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:03:41 by trolland          #+#    #+#             */
/*   Updated: 2024/05/28 19:49:01 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive_signal(int pid, t_char **string, char c)
{
	t_char	*new;

	new = NULL;
	new = ft_new_node(c, pid);
	if (!new)
	{
		free_string(string, pid);
		return ;
	}
	ft_add_back(string, new);
}

t_char	*get_tmp(t_char *string, t_char *tmp, siginfo_t *info)
{
	tmp = string;
	while (tmp && tmp->pid != info->si_pid)
		tmp = tmp->next_pid;
	while (tmp && tmp->last)
		tmp = tmp->last;
	return (tmp);
}

void	send_response(int pid, int num)
{
	usleep(50);
	if (num == SIGUSR1)
		kill(pid, SIGUSR1);
	else if (num == SIGUSR2)
		kill(pid, SIGUSR2);
}

void	receive_and_respond(int num, siginfo_t *info, void *context)
{
	static t_char	*string;
	t_char			*tmp;

	(void)context;
	tmp = NULL;
	tmp = get_tmp(string, tmp, info);
	if (tmp && tmp->pid == info->si_pid && tmp->sig_no >= 0)
	{
		if (tmp->sig_no >= 0 && num == SIGUSR1)
			tmp->c = tmp->c | (1 << tmp->sig_no);
		tmp->sig_no--;
		if (tmp->sig_no < 0 && tmp->c == 0)
			ft_print_string(&string, info->si_pid);
	}
	else if (!tmp || tmp->sig_no < 0)
	{
		if (num == SIGUSR1)
			receive_signal(info->si_pid, &string, (char)(0 | (1 << 7)));
		else
			receive_signal(info->si_pid, &string, 0);
	}
	if (info->si_pid)
		send_response(info->si_pid, num);
}

int	main(void)
{
	int					pid;
	struct sigaction	sig;

	pid = getpid();
	ft_printf("Server PID is [%d]\n", pid);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = receive_and_respond;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
