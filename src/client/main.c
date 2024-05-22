/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:03:38 by trolland          #+#    #+#             */
/*   Updated: 2024/05/22 16:46:00 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	char_to_signal(int pid, char c)
{
	int	i;
	int	temp;

	i = 8;
	while (i--)
	{
		temp = (c >> i) & 1;
		if (temp == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(5);
	}
}

void	tranform_to_signal(int pid, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		char_to_signal(pid, str[i]);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (ft_printf("Enter : ./client [Server PID] [string to send]"));
	if (verify_pid(argv[1]) == -1)
		return (ft_printf("Enter : ./client [Server PID] [string to send]"));
	tranform_to_signal(ft_atoi(argv[1]), argv[2]);
	return (0);
}
