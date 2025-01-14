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

#ifndef __GLIBTOP_PROCSEGMENT_H__
#define __GLIBTOP_PROCSEGMENT_H__

#include <glibtop.h>
#include <glibtop/global.h>

__BEGIN_DECLS

#define GLIBTOP_PROC_SEGMENT_TRS		0
#define GLIBTOP_PROC_SEGMENT_LRS		1
#define GLIBTOP_PROC_SEGMENT_DRS		2
#define GLIBTOP_PROC_SEGMENT_DT			3
#define GLIBTOP_PROC_SEGMENT_START_CODE		4
#define GLIBTOP_PROC_SEGMENT_END_CODE		5
#define GLIBTOP_PROC_SEGMENT_START_STACK	6

#define GLIBTOP_MAX_PROC_SEGMENT		7

typedef struct _glibtop_proc_segment	glibtop_proc_segment;

/* Segment stuff */

struct _glibtop_proc_segment
{
	unsigned long flags;
	long trs,		/* text resident set size */
		lrs,		/* shared-lib resident set size */
		drs,		/* data resident set size */
		dt;		/* dirty pages */
	unsigned long start_code,
				/* address of beginning of code segment */
		end_code,	/* address of end of code segment */
		start_stack;	/* address of the bottom of stack segment */
};

#define glibtop_get_proc_segment(p1, p2)	glibtop_get_proc_segment__r(glibtop_global_server, p1, p2)

extern void glibtop_get_proc_segment__r __P((glibtop *, glibtop_proc_segment *, pid_t));

#ifdef HAVE_GUILE

/* You need to link with -lgtop_guile to get this stuff here. */

extern SCM glibtop_guile_get_proc_segment __P((SCM));

#endif

#ifdef GLIBTOP_GUILE_NAMES

/* You need to link with -lgtop_guile_names to get this stuff here. */

extern SCM glibtop_guile_names_proc_segment __P((void));
extern SCM glibtop_guile_types_proc_segment __P((void));
extern SCM glibtop_guile_labels_proc_segment __P((void));
extern SCM glibtop_guile_descriptions_proc_segment __P((void));

#endif

#ifdef GLIBTOP_NAMES

/* You need to link with -lgtop_names to get this stuff here. */

extern const char *glibtop_types_proc_segment [];
extern const char *glibtop_names_proc_segment [];
extern const char *glibtop_labels_proc_segment [];
extern const char *glibtop_descriptions_proc_segment [];

#endif

__END_DECLS

#endif
