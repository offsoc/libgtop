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

#ifndef __GLIBTOP_SWAP_H__
#define __GLIBTOP_SWAP_H__

#include <glibtop.h>
#include <glibtop/global.h>

__BEGIN_DECLS

#define GLIBTOP_SWAP_TOTAL	0
#define GLIBTOP_SWAP_USED	1
#define GLIBTOP_SWAP_FREE	2

#define GLIBTOP_MAX_SWAP	3

typedef struct _glibtop_swap	glibtop_swap;

struct _glibtop_swap
{
	unsigned long	flags,
		total,		/* GLIBTOP_SWAP_TOTAL	*/
		used,		/* GLIBTOP_SWAP_USED	*/
		free;		/* GLIBTOP_SWAP_FREE	*/
};

#define glibtop_get_swap(swap)	glibtop_get_swap__r(glibtop_global_server, swap)

extern void glibtop_get_swap__r __P((glibtop *, glibtop_swap *));

#ifdef HAVE_GUILE

/* You need to link with -lgtop_guile to get this stuff here. */

extern SCM glibtop_guile_get_swap __P((void));

#endif

#ifdef GLIBTOP_GUILE_NAMES

/* You need to link with -lgtop_guile_names to get this stuff here. */

extern SCM glibtop_guile_names_swap __P((void));
extern SCM glibtop_guile_types_swap __P((void));
extern SCM glibtop_guile_labels_swap __P((void));
extern SCM glibtop_guile_descriptions_swap __P((void));

#endif

#ifdef GLIBTOP_NAMES

/* You need to link with -lgtop_names to get this stuff here. */

extern const char *glibtop_names_swap [];
extern const char *glibtop_types_swap [];
extern const char *glibtop_labels_swap [];
extern const char *glibtop_descriptions_swap [];

#endif

__END_DECLS

#endif
