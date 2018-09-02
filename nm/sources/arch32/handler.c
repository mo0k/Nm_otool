/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/02 22:44:59 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch32.h>

void		handler32(void *ptr, t_meta *meta)
{
	t_header32		*header;
	t_lc			*lc;
	uint32_t		count;
	unsigned char	flag;

	if (!ptr)
		return ;
	flag = 0x03;
	count = 0;
	header = (t_header32*)ptr;
	lc = ptr + sizeof(t_header32);
	meta->swap = (header->magic == MH_CIGAM) ? 1 : 0;
	while (count < SWAP32(meta->swap, header->ncmds))
	{
		get_ptr_lc(meta, lc, ARCH32, &flag);
		lc = (void*)lc + SWAP32(meta->swap, lc->cmdsize);
		++count;
	}
	handler_symtab32((void*)meta->symtab, ptr, meta);
}
