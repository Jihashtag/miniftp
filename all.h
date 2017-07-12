/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:04:02 by jbert             #+#    #+#             */
/*   Updated: 2015/06/05 10:27:40 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ALL_H
# define _ALL_H

# include "libftprintf/printf.h"
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

char	*home_save(char *s);
char	*retcmd(char *s);
void	exec_cmd(char *s);
void	ft_putall(char *s1, char *s2);
void	ft_cd(char *s);
void	ft_pwd(char *s);
int		sock_error(int i);

#endif
