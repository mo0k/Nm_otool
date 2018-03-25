/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/22 22:55:37 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <handler.h>

void		handler32(void *ptr, t_meta *meta)
{
	t_header32	*header;
	t_lc		*lc;
	uint32_t	count;

	if (!ptr)
		return ;
	int first_lc_load_dylib = 1;
	int first_lc_segment = 1;
	count = 0;
	header = (t_header32*)ptr;
	lc = ptr + sizeof(t_header32);
	while (count < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			meta->symtab = lc;
		else if (lc->cmd == LC_LOAD_DYLIB && first_lc_load_dylib)
		{
			meta->dylib = lc;
			first_lc_load_dylib = 0;
		}
		else if (lc->cmd == LC_SEGMENT && first_lc_segment)
		{
			meta->seg32 = lc;
			first_lc_segment = 0;
		}
		lc = (void*)lc + lc->cmdsize;
		++count;
	}
	handler_systab32((void*)meta->symtab, ptr, meta);
}