/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dylibname.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:01:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/01 19:34:55 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>
#include <debug.h>

// Get the dylib libairy name
char 		*get_dylibname(struct load_command *lc, unsigned int index)
{
	P_DEBUG("start get_dylibname()\n");
	unsigned int count;
	t_dylib		*dylib;
	char 		*ptr;

	if (!lc)
		return (NULL);
	count = 0;
	P_DEBUG_VARGS("index:%d\n", index);
	while (count++ < index)
	{
		if (CHK_VAL(g_meta->ptr, g_meta->ptr + g_meta->size, (void*)lc + SWAP32(g_meta->swap, lc->cmdsize)))
			corrupted("get_dylibname 1");
		lc = (void*)lc + SWAP32(g_meta->swap, lc->cmdsize);
	}
	dylib = (t_dylib*)(lc + 1);
	//check dylib strcut
	if (CHK_VAL(g_meta->ptr, g_meta->ptr + g_meta->size, (void*)(dylib + 1))
		|| CHK_VAL(g_meta->ptr, g_meta->ptr + g_meta->size,
			(void*)dylib + SWAP32(g_meta->swap, dylib->name.offset)))
		corrupted("get_dylibname 2");
	ptr = strrchr((void*)dylib + SWAP32(g_meta->swap, dylib->name.offset), '/');
	return ((ptr) ? ptr + 1 : (void*)dylib + SWAP32(g_meta->swap, dylib->name.offset));
	//return ((void*)dylib + dylib->name.offset);
}
