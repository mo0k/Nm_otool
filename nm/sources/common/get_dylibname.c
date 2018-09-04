/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dylibname.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:01:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/03 00:25:18 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

char 		*get_dylibname(struct load_command *lc, unsigned int index)
{
	unsigned int	count;
	t_dylib			*dylib;
	char			*ptr;

	if (!lc)
		return (NULL);
	count = 0;
	while (count++ < index)
	{
		if (CHK_VAL(g_meta, (void*)lc + SWAP32(g_meta->swap, lc->cmdsize)))
			corrupted();
		lc = (void*)lc + SWAP32(g_meta->swap, lc->cmdsize);
	}
	dylib = (t_dylib*)(lc + 1);
	if (CHK_VAL(g_meta, (void*)(dylib + 1))
		|| CHK_VAL(g_meta,
			(void*)dylib + SWAP32(g_meta->swap, dylib->name.offset)))
		corrupted();
	ptr = ft_strrchr((void*)dylib + SWAP32(g_meta->swap, dylib->name.offset)
						, '/');
	return ((ptr) ? ptr + 1
					: (void*)dylib + SWAP32(g_meta->swap, dylib->name.offset));
}
