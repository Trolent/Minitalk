/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:03:41 by trolland          #+#    #+#             */
/*   Updated: 2024/05/15 14:31:33 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive_signal(int num)
{
	static int	i = 7;
	static char	c = 0;

	if (num == SIGUSR1)
		c = c | (1 << i);
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
	int	pid;

	pid = getpid();
	ft_printf("Server PID is [%d]\n", pid);
	signal(SIGUSR1, receive_signal);
	signal(SIGUSR2, receive_signal);
	while (1)
	{
	}
	return (0);
}
