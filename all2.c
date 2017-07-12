/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:19:41 by jbert             #+#    #+#             */
/*   Updated: 2015/06/05 10:22:27 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	ft_pwd(char *s)
{
	if (*(s + 4))
		ft_putstr("pwd should not take any arguments\n");
	else
	{
		s = getcwd(s, 1025);
		if (ft_strncmp(home_save(NULL), s, ft_strlen(home_save(NULL)) + 1) == 0)
			ft_putstr("/\n");
		else
			ft_putall(&(s[ft_strlen(home_save(NULL))]), "\n");
	}
}
