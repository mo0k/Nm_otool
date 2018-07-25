/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:24:02 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/24 19:56:05 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/open_file.h"

static char	**get_strerror()
{
	static char	*error[] = 
	{
		"Arguments no valid",
		"Error open",
		"Error fstat",
		"Is a directory",
		"Error mmap"
	};
	return (error);
}

int 	open_file(void **ptr, size_t *ptr_size, char *filepath, int flag_open)
{
	int				fd;
	struct stat		buff;

	if ((fd = open(filepath, flag_open)) < 0)
		return (ERROR_OPEN);	
	if (fstat(fd, &buff) == -1)
		return (ERROR_FSTAT);
	if (buff.st_mode & S_IFDIR)
		return (ERROR_ISDIR);
	*ptr_size = buff.st_size;
	if ((*ptr = mmap(0, *ptr_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (ERROR_MMAP);
	return (0);
}

void		open_error(unsigned int error, char *pathfile)
{
	if (error > 4)
		return ;
	else
		ft_dprintf(2, "ft_nm: %s %s\n", pathfile, get_strerror()[error]);
	return ;
}
