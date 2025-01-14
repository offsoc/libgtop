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

#include <glibtop.h>
#include <glibtop/prockernel.h>

static const unsigned long _glibtop_sysdeps_proc_kernel =
(1 << GLIBTOP_PROC_KERNEL_K_FLAGS) + (1 << GLIBTOP_PROC_KERNEL_MIN_FLT) +
(1 << GLIBTOP_PROC_KERNEL_MAJ_FLT) + (1 << GLIBTOP_PROC_KERNEL_CMIN_FLT) +
(1 << GLIBTOP_PROC_KERNEL_CMAJ_FLT) + (1 << GLIBTOP_PROC_KERNEL_KSTK_ESP) +
(1 << GLIBTOP_PROC_KERNEL_KSTK_EIP) + (1 << GLIBTOP_PROC_KERNEL_WCHAN);

/* Provides detailed information about a process. */

void
glibtop_get_proc_kernel__r (glibtop *server, glibtop_proc_kernel *buf, pid_t pid)
{
	char input [BUFSIZ], *tmp;
	int nread;
	FILE *f;
	
	glibtop_init__r (&server);

	memset (buf, 0, sizeof (glibtop_proc_kernel));

	if (pid == 0) {
		/* Client is only interested in the flags. */
		buf->flags = _glibtop_sysdeps_proc_kernel;
		return;
	}

	sprintf (input, "/proc/%d/stat", pid);

	f = fopen (input, "r");
	if (!f) return;
	
	nread = fread (input, 1, BUFSIZ, f);
	
	if (nread < 0) {
		fclose (f);
		return;
	}
	
	input [nread] = 0;
	
	/* This is from guile-utils/gtop/proc/readproc.c */
	
	/* split into "PID (cmd" and "<rest>" */
	tmp = strrchr (input, ')');
	*tmp = '\0';		/* replace trailing ')' with NUL */
	/* parse these two strings separately, skipping the leading "(". */

	sscanf(tmp + 2,		/* skip space after ')' too */
	       "%*c %*d %*d %*d %*d %*d %lu %lu %lu %lu %lu "
	       "%*d %*d %*d %*d %*d %*d %*u %*u %*d %*u "
	       "%*u %*u %*u %*u %*u %lu %lu %*d %*d %*d %*d %lu",
	       &buf->k_flags, &buf->min_flt, &buf->cmin_flt,
	       &buf->maj_flt, &buf->cmaj_flt, &buf->kstk_esp,
	       &buf->kstk_eip, &buf->wchan);
	
	fclose (f);

	buf->flags = _glibtop_sysdeps_proc_kernel;
}
