/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:24:02 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/09 13:54:37 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/open_file.h"

int 	open_file(void **ptr, size_t *ptr_size, char *filepath, int flag_open)
{
	int				fd;
	struct stat		buff;

	//P_DEBUG_VARGS("filepath:%s\n", filepath);
	if ((fd = open(filepath, flag_open)) < 0)
	{
		//perror(ERROR_STR);
		return (ERROR_OPEN);	
	}
	if (fstat(fd, &buff) == -1)
	{
		//perror(ERROR_STR);
		return (ERROR_FSTAT);
	}
	//check si dossier
	*ptr_size = buff.st_size;
	if ((*ptr = mmap(0, *ptr_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		//perror(ERROR_STR);
		return (ERROR_MMAP);
	}
	//P_DEBUG("load file OK\n");
	return (0);
}