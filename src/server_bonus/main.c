/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:03:41 by trolland          #+#    #+#             */
/*   Updated: 2024/05/25 17:48:38 by trolland         ###   ########.fr       */
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

void	receive_and_respond(int num, siginfo_t *info, void *context)
{
	static t_char	*string;
	t_char			*tmp;

	(void)context;
	tmp = string;
	while (tmp && tmp->pid != info->si_pid)
		tmp = tmp->next_pid;
	while (tmp && tmp->last)
		tmp = tmp->last;
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
	{
		usleep(50);
		if (num == SIGUSR1)
			kill(info->si_pid, SIGUSR1);
		else if (num == SIGUSR2)
			kill(info->si_pid, SIGUSR2);
	}
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
