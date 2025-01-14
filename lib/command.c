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

#include <glibtop/read.h>
#include <glibtop/write.h>
#include <glibtop/read_data.h>

#include <glibtop/command.h>
#include <glibtop/xmalloc.h>

void *
glibtop_call__r (glibtop *server, unsigned command, size_t send_size, void *send_buf,
		 size_t recv_size, void *recv_buf)
{
	glibtop_command *cmnd;
	void *ptr;

	glibtop_init__r (&server);

	cmnd = glibtop_calloc__r (server, 1, sizeof (glibtop_command));
	
	memcpy (&cmnd->server, server, sizeof (glibtop));
	
	cmnd->command = command;
	cmnd->size = send_size;
	
	glibtop_write__r (server, sizeof (glibtop_command), cmnd);
	glibtop_write__r (server, send_size, send_buf);
	glibtop_read__r  (server, recv_size, recv_buf);
	
	ptr = glibtop_read_data__r (server);
	
	glibtop_free__r (server, cmnd);
	
	return ptr;
}
