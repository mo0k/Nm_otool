/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_lc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 16:47:53 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/02 21:31:06 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

void		get_ptr_lc(t_meta *meta, t_lc *lc, enum e_archtype archtype, \
																uint8_t *flag)
{
	if (CHK_VAL(meta, (void*)lc)
		|| CHK_VAL(meta, (void*)lc + SWAP32(meta->swap, lc->cmdsize)))
		corrupted();
	if (SWAP32(meta->swap, lc->cmd) == LC_SYMTAB)
		meta->symtab = lc;
	else if (SWAP32(meta->swap, lc->cmd) == LC_LOAD_DYLIB && (*flag & 0x01))
	{
		meta->dylib = lc;
		*flag ^= 0x01; //set first bit at 0
	}
	else if ((SWAP32(meta->swap, lc->cmd) == LC_SEGMENT ||
			(SWAP32(meta->swap, lc->cmd) == LC_SEGMENT_64)) &&
			(*flag & 0x02))
	{
		if (archtype == ARCH32)
			meta->seg32 = lc;
		else
			meta->seg64 = lc;
		*flag ^= 0x02; //set second bit at 0
	}
}