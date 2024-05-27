/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:49:40 by trolland          #+#    #+#             */
/*   Updated: 2024/05/25 17:52:42 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_char	*ft_new_node(char c, int pid)
{
	t_char	*new;

	new = (t_char *)malloc(sizeof(t_char));
	if (!new)
		return (NULL);
	new->sig_no = 6;
	new->c = c;
	new->pid = pid;
	new->next = NULL;
	new->next_pid = NULL;
	new->last = NULL;
	return (new);
}

void	ft_add_back(t_char **lst, t_char *new)
{
	t_char	*tmp;
	t_char  *lead;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while(tmp->pid != new->pid && tmp->next_pid)
		tmp = tmp->next_pid;
	if (tmp->pid == new->pid)
	{
		lead = tmp;
		while (tmp->last)
			tmp = tmp->last;
		tmp->next = new;
		lead->last = new;
	}
	else if (!tmp->next_pid)
	{
		tmp->next_pid = new;
		return ;
	}
}

void	free_lst(t_char *lst)
{
	t_char	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	free_string(t_char **string, int pid)
{
	t_char	*tmp;
	t_char  *lead;

	lead = *string;
	if (lead->pid == pid)
	{
		*string = lead->next_pid;
		free_lst(lead);
		return ;
	}
	else if (lead->next_pid && lead->next_pid->pid == pid)
	{
		tmp = lead->next_pid;
		lead->next_pid = lead->next_pid->next_pid;
		free_lst(tmp);
		return ;
	}
}

void	ft_print_string(t_char **string, int pid)
{
	t_char	*tmp;

	tmp = *string;
	while(tmp && tmp->pid != pid)
		tmp = tmp->next_pid;
	if (!tmp)
		return ;
	while (tmp)
	{
		ft_printf("%c", tmp->c);
		tmp = tmp->next;
	}
	ft_printf("\n");
	free_string(string, pid);
}

simultaniously 