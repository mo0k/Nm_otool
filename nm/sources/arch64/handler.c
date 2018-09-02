/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/02 22:59:19 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch64.h>

void		handler64(void *ptr, t_meta *meta)
{
	t_header64	*header;
	t_lc		*lc;
	uint32_t	count;
	uint8_t		flag;

	if (!ptr)
		return ;
	flag = 0x03;
	count = 0;
	header = (t_header64*)ptr;
	if (CHK_VAL(meta, (void*)header))
		corrupted();
	lc = ptr + sizeof(t_header64);
	meta->swap = (header->magic == MH_CIGAM_64) ? 1 : 0;
	while (count < SWAP32(meta->swap, header->ncmds))
	{
		get_ptr_lc(meta, lc, ARCH64, &flag);
		lc = (void*)lc + SWAP32(meta->swap, lc->cmdsize);
		++count;
	}
	handler_symtab64((void*)meta->symtab, ptr, meta);
}
