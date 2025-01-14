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

#ifndef __GLIBTOP_MACHINE_H__
#define __GLIBTOP_MACHINE_H__

/* make sure param.h gets loaded with KERNEL defined to get PZERO & NZERO */
#define KERNEL
#include <sys/param.h>
#undef KERNEL

#include <stdio.h>
#include <kvm.h>
#include <nlist.h>
#include <math.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/dk.h>
#include <sys/vm.h>
#include <sys/file.h>
#include <sys/time.h>
#include <vm/page.h>

#ifdef solbourne
#include <sys/syscall.h>
#endif

__BEGIN_DECLS

/* Older versions of SunOS don't have a typedef for pid_t.
   Hopefully this will catch all those cases without causing other problems.
 */
#ifndef __sys_stdtypes_h
typedef int pid_t;
#endif

/* definitions for indices in the nlist array */
#define X_AVENRUN	0
#define X_CCPU		1
#define X_MPID		2
#define X_NPROC		3
#define X_PROC		4
#define X_TOTAL		5
#define X_CP_TIME	6
#define X_PAGES		7
#define X_EPAGES	8

#ifdef MULTIPROCESSOR
#define X_NCPU		9
#define X_MP_TIME	10
#endif

/* Log base 2 of 1024 is 10 (2^10 == 1024) */
#define LOG1024         10

typedef struct _glibtop_machine		glibtop_machine;

struct _glibtop_machine
{
	uid_t uid, euid;		/* Real and effective user id */
	gid_t gid, egid;		/* Real and effective group id */
	int nlist_count;		/* Number of symbols in the nlist */
	int ncpu;			/* Number of CPUs we have */
	unsigned long pages, epages;
	struct page *physpage;
	int bytesize, count;
	int pageshift;			/* log base 2 of the pagesize */
	kvm_t *kd;
};

/* Those functions are used internally in libgtop */

#ifdef _IN_LIBGTOP

extern struct nlist _glibtop_nlist[];

extern int _glibtop_check_nlist __P((void *, register struct nlist *));

extern int _glibtop_getkval __P((void *, unsigned long, int *, int, char *));

#endif

__END_DECLS

#endif
