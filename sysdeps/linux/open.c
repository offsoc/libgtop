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

#include <glibtop/open.h>

/* =====================================================
 * Linux kernel version information for procps utilities
 * Copyright (c) 1996 Charles Blake <cblake@bbn.com>
 */
#include <sys/utsname.h>

#define LINUX_VERSION(x,y,z)   (0x10000*(x) + 0x100*(y) + z)

static int linux_version_code = 0;

static void set_linux_version(void) {
    static struct utsname uts;
    int x = 0, y = 0, z = 0;	/* cleared in case sscanf() < 3 */
    
    if (linux_version_code) return;
    if (uname(&uts) == -1)	/* failure most likely implies impending death */
	exit(1);
    if (sscanf(uts.release, "%d.%d.%d", &x, &y, &z) < 3)
	fprintf(stderr,		/* *very* unlikely to happen by accident */
		"Non-standard uts for running kernel:\n"
		"release %s=%d.%d.%d gives version code %d\n",
		uts.release, x, y, z, LINUX_VERSION(x,y,z));
    linux_version_code = LINUX_VERSION(x, y, z);
}

/* ======================================================= */

/* Opens pipe to gtop server. Returns 0 on success and -1 on error. */

void
glibtop_open (glibtop *server, const char *program_name)
{
	memset (server, 0, sizeof (glibtop));
	server->name = program_name;

	set_linux_version ();
	server->os_version_code = (unsigned long) linux_version_code;
}
