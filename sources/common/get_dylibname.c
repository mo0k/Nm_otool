/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dylibname.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:01:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/25 14:56:15 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

// Get the dylib libairy name
char 		*get_dylibname(struct load_command *lc, unsigned int index)
{
	unsigned int count;
	t_dylib		*dylib;
	char 		*ptr;

	if (!lc)
		return (NULL);
	count = 0;
	while (count++ < index)
		lc = (void*)lc + lc->cmdsize;
	dylib = (t_dylib*)(lc + 1);
	ptr = strrchr((void*)dylib + dylib->name.offset, '/');
	return ((ptr) ? ptr + 1 : (void*)dylib + dylib->name.offset);
	//return ((void*)dylib + dylib->name.offset);
}
