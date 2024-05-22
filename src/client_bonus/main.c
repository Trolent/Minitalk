/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:03:38 by trolland          #+#    #+#             */
/*   Updated: 2024/05/22 16:47:47 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_responded = 0;

void	response(int num)
{
	if (num == SIGUSR1)
		g_responded = 1;
	if (num == SIGUSR2)
		g_responded = 1;
}

int	char_to_signal(int pid, char c)
{
	int	i;
	int	temp;

	i = 8;
	while (i--)
	{
		g_responded = 0;
		temp = (c >> i) & 1;
		if (temp == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_responded)
			pause();
		usleep(50);
	}
	return (1);
}

void	tranform_to_signal(int pid, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != 0)
		if (!char_to_signal(pid, str[i]))
			return ;
	if (char_to_signal(pid, 0) == 1 && g_responded == 1)
		ft_printf("message received\n");
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (ft_printf("Enter : ./client [Server PID] [string to send]"));
	if (verify_pid(argv[1]) == -1)
		return (ft_printf("Enter : ./client [Server PID] [string to send]"));
	signal(SIGUSR1, response);
	signal(SIGUSR2, response);
	tranform_to_signal(ft_atoi(argv[1]), argv[2]);
	return (0);
}
