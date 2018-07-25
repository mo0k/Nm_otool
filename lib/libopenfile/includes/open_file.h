/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 06:51:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/24 19:56:25 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_FILE_H
# define OPEN_FILE_H

# include <sys/stat.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <stdio.h>

enum e_return
{
	ERROR_ARGS,
	ERROR_OPEN,
	ERROR_FSTAT,
	ERROR_ISDIR,
	ERROR_MMAP
};

int 	open_file(void **ptr, size_t *ptr_size, char *filepath, int flag_open);
void	open_error(unsigned int error, char *pathfile);

#endif