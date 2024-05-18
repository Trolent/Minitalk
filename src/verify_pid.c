/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:45:51 by trolland          #+#    #+#             */
/*   Updated: 2024/05/18 12:48:32 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	verify_pid(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
	}
	return (0);
}
