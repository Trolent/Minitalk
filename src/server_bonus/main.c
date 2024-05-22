/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:03:41 by trolland          #+#    #+#             */
/*   Updated: 2024/05/22 16:47:11 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive_and_respond(int num, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	c = 7;

	(void)context;
	if (num == SIGUSR1)
		c = c | (1 << i);
	i--;
	if (i == -1)
	{
		if (c == 0)
			ft_printf("\n");
		else
			ft_printf("%c", c);
		c = 0;
		i = 7;
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
