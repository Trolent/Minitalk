/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trolland <trolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:07 by trolland          #+#    #+#             */
/*   Updated: 2024/05/30 09:54:59 by trolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_char
{
	char			sig_no;
	char			c;
	int				pid;
	struct s_char	*next;
	struct s_char	*next_pid;
	struct s_char	*last;

}					t_char;

t_char				*ft_new_node(char c, int pid);
void				ft_add_back(t_char **lst, t_char *new);
void				free_lst(t_char *lst);
void				free_string(t_char **string, int pid);
void				ft_print_string(t_char **string, int pid);

int					verify_pid(char *str);

#endif
