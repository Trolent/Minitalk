/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:03:38 by trolland          #+#    #+#             */
/*   Updated: 2024/05/21 17:47:54 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_struct
{
	int	responded;
	int	signal;
}		t_struct;

t_struct test;

void	response(int num)
{
	if (num == test.signal)
	{
		test.responded = 1;
	}
}
int	char_to_signal(int pid, char c)
{
	int	i;
	int	temp;

	i = 8;
	while (i--)
	{
		test.responded = 0;
		temp = (c >> i) & 1;
		if (temp == 1)
		{	
			test.signal = SIGUSR1;
			kill(pid, SIGUSR1);
		}
		else
		{
			test.signal = SIGUSR2;
			kill(pid, SIGUSR2);
		}
		usleep(50);
		pause();
		if (test.responded == 0)
		{
			ft_printf("Error transmitting message\n");
			return(0);
		}
	}
	return (1);
}

void	tranform_to_signal(int pid, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != 0)
		if (!char_to_signal(pid, str[i]))
			return;
	printf("message received\n");
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
