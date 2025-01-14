/* $Id$ */

/* Copyright (C) 1995, 1996, 1997 Free Software Foundation, Inc.
   This file is part of the Gnome Top Library.
   Contributed by Martin Baulig <martin@home-of-linux.org>, April 1998.

   The Gnome Top Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The Gnome Top Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include <config.h>
#include <glibtop/error.h>
#include <glibtop/loadavg.h>

static const unsigned long _glibtop_sysdeps_loadavg =
(1 << GLIBTOP_LOADAVG_LOADAVG);

/* Provides load averange. */

void
glibtop_get_loadavg__r (glibtop *server, glibtop_loadavg *buf)
{
	struct tbl_loadavg loadavg;
	int ret;

	glibtop_init ();

	memset (buf, 0, sizeof (glibtop_loadavg));
	
	ret = table (TBL_LOADAVG, 0, (char *) &loadavg, 1,
		     sizeof (struct tbl_loadavg)); 

	if (ret != 1) return;

	buf->flags = _glibtop_sysdeps_loadavg;
		
	if (loadavg.tl_lscale == 0) {
		buf->loadavg [0] = loadavg.tl_avenrun.d [0];
		buf->loadavg [1] = loadavg.tl_avenrun.d [1];
		buf->loadavg [2] = loadavg.tl_avenrun.d [2];
	} else {
		buf->loadavg [0] = 
			(double) loadavg.tl_avenrun.l [0] /
			(double) loadavg.tl_mach_factor [0];
		buf->loadavg [1] =
			(double) loadavg.tl_avenrun.l [1] 
			/ (double) loadavg.tl_mach_factor [1];
		buf->loadavg [2] =
			(double) loadavg.tl_avenrun.l [2] /
			(double) loadavg.tl_mach_factor [2];
	}
}
