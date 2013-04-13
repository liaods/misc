/*
 *  fb2modeline.c - change fbmode timings to modeline in xorg.conf
 *
 *  Copyright (C) 2013 Liaods <dongsheng.liao@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or (at
 *  your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */
#include <stdio.h>
int main(int argc, char **argv)
{

	int x, y, rate, pclk, l, r, u, d, hs, vs;
	int i=0;
	float clock;

	int dst[8];
	if ( argc != 11 )
	{
		printf("Usage: %s x y rate timings\n", argv[i]);
		printf("timings are: pclk left right up down hs vs\n");
		return -1;
	}
	x=atoi(argv[++i]);
	y=atoi(argv[++i]);
	rate=atoi(argv[++i]);
	pclk = atoi(argv[++i]);
	l=atoi(argv[++i]);
	r=atoi(argv[++i]);
	u=atoi(argv[++i]);
	d=atoi(argv[++i]);
	hs=atoi(argv[++i]);
	vs=atoi(argv[++i]);

	clock = 1000000*1.0/pclk;
	dst[0] = x;
	dst[1] = r + x;
	dst[2] = dst[1] + hs;
	dst[3] = dst[2] + l;

	dst[4] = y;
	dst[5] = d + y;
	dst[6] = dst[5] + vs;
	dst[7] = dst[6] + u;
	printf("Modeline \"%dx%d-%d\"  %.2f", x, y, rate, clock);
	for(i=0; i<8; ++i)
		printf("  %d", dst[i]);
	/* TODO, should we care about this? */
	printf(" -HSync +Vsync\n");
	return 0;
}

