/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 14:17:05 by jbert             #+#    #+#             */
/*   Updated: 2015/06/05 10:34:12 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serv.h"

void	ft_wait(int s)
{
	if (s == SIGCHLD)
		wait4(-1, NULL, WUNTRACED, NULL);
}

t_serv	*sserv(t_serv *s)
{
	static t_serv	*serv = NULL;

	if (s)
		serv = s;
	return (serv);
}

int		ft_end(int fd, int s)
{
	if (fd == -1)
		exit_error();
	if (sserv(NULL)->pid == 0 && read_sock(fd) < 0)
		return (ft_putstr_fd("Error while reading socks\n", 2));
	close(fd);
	if (sserv(NULL)->pid != 0)
	{
		if (sserv(NULL)->prev)
			sserv(NULL)->prev->next = sserv(NULL)->next;
		if (sserv(NULL)->next)
			sserv(NULL)->next->prev = sserv(NULL)->prev;
		free(sserv(NULL));
		free(home_save(NULL));
		close(s);
	}
	ft_putstr("Client quit\n");
	return (0);
}

void	ft_start(char **av)
{
	if (av[2] && chdir(av[2]) != -1)
		ft_printf("Server root is : [%s]\n", home_save(getcwd(NULL, 1025)));
	else
		home_save(getcwd(NULL, 1025));
	signal(SIGCHLD, ft_wait);
}

int		main(int ac, char **av)
{
	int					p;
	int					s;
	int					fd;
	unsigned int		fdlen;
	struct sockaddr_in	fdaddr;

	if (ac < 2)
		return (ft_putstr_fd("Error : not enough arguments\n", 2));
	ft_start(av);
	p = ft_atoi(av[1]);
	if (p <= 0)
		return (ft_putstr_fd("Error : port should be positive\n", 2));
	s = ret_sock(p);
	if (s <= 0)
		return (sock_error(s));
	while ((fd = accept(s, (struct sockaddr *)&fdaddr, &fdlen)) != -1)
	{
		sserv(new_client(sserv(NULL)));
		if (sserv(NULL)->pid == 0)
			break ;
		while (sserv(NULL)->prev)
			sserv(sserv(NULL)->prev);
	}
	return (ft_end(fd, s));
}
