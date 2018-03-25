/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_stab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 22:46:48 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/22 22:48:14 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

char *get_type_stab(uint8_t ntype)
{
	int				i;
	static int		tab_i[] = {0X20, 0x22, 0x24, 0x26, 0x28, 0x2e, 0x32, 0x3c,
	0x40, 0x44, 0x4e, 0x60, 0x64, 0x66, 0x80, 0x82,
	0x84, 0x86, 0x88, 0x8A, 0xa0, 0xa2, 0xa4, 0xc0,
	0xc2, 0xe0, 0xe2, 0xe4, 0xe8, 0xfe};
	static char		*tab_s[] = {"GSYM", "FNAME", "FUN", "STSYM", "LCSYM",
								"BNSYM", "AST", "OPT", "RSYM", "SLINE",
								"ENSYM", "SSYM", "SO", "OSO", "LSYM",
								"BINCL", "SOL", "PARAMS", "VERSION", "OLEVEL",
								"PSYM", "EINCL", "ENTRY", "LBRAC", "EXCL",
								"RBRAC", "BCOMM", "ECOMM", "ECOML", "LENG"};

	i = -0x1;
	while (++i < 30)
		if (ntype == tab_i[i])
			return (tab_s[i]);
	return (NULL);
}