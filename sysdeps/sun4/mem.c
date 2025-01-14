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
#include <glibtop/mem.h>

static const unsigned long _glibtop_sysdeps_mem =
(1 << GLIBTOP_MEM_TOTAL) + (1 << GLIBTOP_MEM_USED) +
(1 << GLIBTOP_MEM_FREE) + (1 << GLIBTOP_MEM_LOCKED);

/* define pagetok in terms of pageshift */

#define pagetok(size) ((size) << server->machine.pageshift)

/* Provides information about memory usage. */

void
glibtop_get_mem__r (glibtop *server, glibtop_mem *buf)
{
	memset (buf, 0, sizeof (glibtop_mem));
	
	/* !!! THE FOLLOWING CODE RUNS SGID KMEM - CHANGE WITH CAUTION !!! */
	
	setregid (server->machine.gid, server->machine.egid);
	
	/* get the array of physpage descriptors */
	
	(void) _glibtop_getkval (server, server->machine.pages,
				 (int *) server->machine.physpage,
				 server->machine.bytesize,
				 "array _page");
	
	if (setregid (server->machine.egid, server->machine.gid))
		_exit (1);
	
	/* !!! END OF SGID KMEM PART !!! */


	{	/* sum memory statistics */
		register struct page *pp;
		register int cnt;
		register int inuse;
		register int free;
		register int locked;
		
		/* bop thru the array counting page types */

		pp = server->machine.physpage;
		inuse = free = locked = 0;
		for (cnt = server->machine.count; --cnt >= 0; pp++) {
			if (pp->p_free)
				free++;
			else if (pp->p_lock || pp->p_keepcnt > 0)
				locked++;
			else
				inuse++;
		}

		/* convert memory stats to Kbytes */
		
		buf->total  = pagetok (inuse + free);
		buf->used   = pagetok (inuse);
		buf->free   = pagetok (free);
		buf->locked = pagetok (locked);

		buf->flags = _glibtop_sysdeps_mem;
	}
}
