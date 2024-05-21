/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:03:41 by trolland          #+#    #+#             */
/*   Updated: 2024/05/21 17:05:46 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive_and_respond(int num, siginfo_t *info, void *context)
{
	static int	i = 7;
	static char	c = 0;

	(void)context;
	if (num == SIGUSR1)
	{
		c = c | (1 << i);
		kill(info->si_pid, SIGUSR1);
	}
	else
		kill(info->si_pid, SIGUSR1);
	i--;
	if (i == -1)
	{
		ft_printf("%c", c);
		i = 7;
		c = 0;
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
