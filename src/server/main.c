/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:03:41 by trolland          #+#    #+#             */
/*   Updated: 2024/05/24 20:12:51 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive_signal(int num)
{
	static int		i = 7;
	static char		c = 0;
	t_char			*new;
	static t_char	*string;

	new = NULL;
	if (num == SIGUSR1)
		c = c | (1 << i);
	i--;
	if (i == -1)
	{
		new = ft_new_node(c);
		if (!new)
		{
			free_string(string);
			return ;
		}
		ft_add_back(&string, new);
		if (c == 0)
		{
			ft_print_string(&string);
		}
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
