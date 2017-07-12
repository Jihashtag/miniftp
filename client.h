/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:04:50 by jbert             #+#    #+#             */
/*   Updated: 2015/06/05 10:26:34 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CLIENT_H
# define _CLIENT_H

# include "all.h"

int		ret_sock(char *host, int p);
void	ft_send(char *s, int fd);
void	ft_get(char *s, int fd);
void	ft_put(char *s, int sock);

#endif
