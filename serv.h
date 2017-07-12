/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:02:21 by jbert             #+#    #+#             */
/*   Updated: 2015/06/05 10:35:39 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERV_H
# define _SERV_H

# include "all.h"

typedef struct	s_serv
{
	pid_t			pid;
	struct s_serv	*next;
	struct s_serv	*prev;
}				t_serv;

int				ret_sock(int p);
void			ft_get(char *s, int sock);
void			ft_put(char *s, int fd);
void			error(char *s);
int				action(char *s, int fd);

int				read_sock(int fd);
int				sock_error(int i);
t_serv			*new_client(t_serv *serv);
void			exit_error(void);

#endif
