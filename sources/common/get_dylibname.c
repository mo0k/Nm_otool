/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dylibname.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:01:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 17:58:19 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

// Get the dylib libairy name
char 		*get_dylibname(struct load_command *lc, unsigned int index)
{
	unsigned int count;
	t_dylib		*dylib;

	if (!lc)
		return (NULL);
	count = 0;
	while (count++ < index)
		lc = (void*)lc + lc->cmdsize;
	dylib = (t_dylib*)(lc + 1);
	return ((void*)dylib + dylib->name.offset);
}
