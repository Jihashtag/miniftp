/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:33:44 by jbert             #+#    #+#             */
/*   Updated: 2015/06/05 10:34:07 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serv.h"

int		read_sock(int fd)
{
	int		ret;
	char	buff[1025];

	ft_bzero(buff, 1025);
	dup2(fd, 1);
	dup2(fd, 2);
	while ((ret = read(fd, buff, 1024)) > 0)
	{
		buff[ret - 1] = '\0';
		if (!action(buff, fd))
			break ;
		ft_bzero(buff, 1025);
	}
	dup2(0, 2);
	dup2(0, 1);
	return (ret);
}

int		sock_error(int i)
{
	if (i == 0)
		return (ft_putstr_fd("Error : could not create socket\n", 2));
	if (i == -1)
		return (ft_putstr_fd("Error : could not get protocol by name\n", 2));
	if (i == -2)
		return (ft_putstr_fd("Error : could not bind\n", 2));
	if (i == -3)
		return (ft_putstr_fd("Error : could not listen\n", 2));
	return (-1);
}

t_serv	*new_client(t_serv *serv)
{
	t_serv	*tmp;

	tmp = NULL;
	if (serv)
	{
		while (serv != NULL)
		{
			tmp = serv;
			serv = serv->next;
		}
	}
	serv = (t_serv *)malloc(sizeof(t_serv));
	serv->next = NULL;
	serv->prev = tmp;
	if (tmp)
		tmp->next = serv;
	serv->pid = fork();
	return (serv);
}

void	exit_error(void)
{
	exit(5);
}
