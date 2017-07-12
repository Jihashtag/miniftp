/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:25:14 by jbert             #+#    #+#             */
/*   Updated: 2015/06/05 10:26:39 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		ret_sock(char *host, int p)
{
	int					s;
	struct protoent		*prot;
	struct sockaddr_in	saddr;

	prot = getprotobyname("tcp");
	if (!prot)
		return (-1);
	s = socket(PF_INET, SOCK_STREAM, prot->p_proto);
	if (s == -1)
		return (0);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(p);
	if (!ft_strcmp(host, "localhost"))
		saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	else
		saddr.sin_addr.s_addr = inet_addr(host);
	if (connect(s, (const struct sockaddr *)&saddr, sizeof(saddr)) != 0)
		return (-2);
	return (s);
}

void	ft_send(char *s, int fd)
{
	char	tmp[1025];
	int		ret;

	send(fd, s, 1025, 0);
	ft_bzero(tmp, 1025);
	while ((ret = recv(fd, tmp, 1024, 0)) > 0)
	{
		write(1, tmp, ret);
		if (ret < 1024 && tmp[ret - 2] == '\n' && tmp[ret - 1] == '\0')
			break ;
	}
	if (ret <= 0)
		ft_putstr_fd("\nAn error occured\n", 2);
}

void	ft_get(char *s, int fd)
{
	char	tmp[1025];
	int		ret;
	int		file;

	send(fd, s, 1024, 0);
	ft_bzero(tmp, 1025);
	recv(fd, tmp, 1020, 0);
	if (ft_strncmp(&(tmp[ft_strlen(s) - 4]), \
		" : got an error while opening", 29) != 0)
		file = open(tmp, O_RDWR | O_CREAT, S_IRWXU);
	else
	{
		ft_putstr_fd("We could not open your file ...\n", 2);
		return ;
	}
	while ((ret = recv(fd, tmp, 1024, 0)) > 0)
	{
		ret = write(file, tmp, ret);
		if (ret < 1024)
			break ;
	}
	if (ret <= 0)
		ft_putstr_fd("\nAn error occured\n", 2);
}

void	ft_put(char *s, int sock)
{
	int		fd;
	char	buff[1025];
	int		ret;

	fd = open(s + 4, O_RDONLY);
	if (fd <= 0)
	{
		ft_putall(s, " : got an error while opening\n");
		return ;
	}
	send(sock, s, 1024, 0);
	ft_bzero(buff, 1025);
	read(sock, buff, 1024);
	if (ft_strncmp(buff, "ok", 2) != 0)
	{
		ft_putstr_fd(s + 4, 2);
		ft_putstr_fd(" : this file could not be created on the server\n", 2);
		return ;
	}
	while ((ret = read(fd, buff, 1024)) > 0)
	{
		send(sock, buff, ret, 0);
		ft_bzero(buff, ret);
	}
	close(fd);
}
