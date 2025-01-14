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

#ifndef __GLIBTOP_H__
#define __GLIBTOP_H__

#include <glibtop/global.h>

#ifdef HAVE_GLIBTOP_MACHINE_H
#include <glibtop_machine.h>
#endif

typedef struct _glibtop		glibtop;

struct _glibtop
{
	int fd;				/* Server file descriptor */
#ifdef HAVE_GLIBTOP_MACHINE_H
	glibtop_machine machine;	/* Machine dependent data */
#endif
	int input [2];			/* Pipe client <- server */
	int output [2];			/* Pipe client -> server */
	unsigned long os_version_code;	/* Version code of the operating system */
	const char *name;		/* Program name for error messages */
	pid_t pid;			/* PID of the server */
};

extern glibtop *glibtop_global_server;

#define glibtop_init()	glibtop_init__r(&glibtop_global_server);

extern glibtop *glibtop_init__r __P((glibtop **));

#ifdef HAVE_GUILE

/* You need to link with -lgtop_guile to get this stuff here. */

extern void glibtop_boot_guile __P((void));

#endif

#ifdef GLIBTOP_GUILE_NAMES

/* You need to link with -lgtop_guile_names to get this stuff here. */

extern void glibtop_boot_guile_names __P((void));

#ifndef GLIBTOP_NAMES
#define GLIBTOP_NAMES
#endif

#endif

#endif
