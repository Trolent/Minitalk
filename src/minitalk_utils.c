/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:49:40 by trolland          #+#    #+#             */
/*   Updated: 2024/05/25 14:54:15 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_char	*ft_new_node(char c)
{
	t_char	*new;

	new = (t_char *)malloc(sizeof(t_char));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	new->last = NULL;
	return (new);
}

void	ft_add_back(t_char **lst, t_char *new)
{
	t_char	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->last)
		tmp = tmp->last;
	tmp->next = new;
	(*lst)->last = new;
}

void	free_string(t_char *string)
{
	t_char	*tmp;

	while (string)
	{
		tmp = string;
		string = string->next;
		free(tmp);
	}
}

void	ft_print_string(t_char **string)
{
	t_char	*tmp;

	tmp = *string;
	while (tmp)
	{
		ft_printf("%c", tmp->c);
		tmp = tmp->next;
	}
	ft_printf("\n");
	free_string(*string);
	*string = NULL;
}
