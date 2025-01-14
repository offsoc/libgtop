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

#ifndef __GLIBTOP_UNION_H__
#define __GLIBTOP_UNION_H__

#include <glibtop/cpu.h>
#include <glibtop/mem.h>
#include <glibtop/swap.h>
#include <glibtop/uptime.h>
#include <glibtop/loadavg.h>
#include <glibtop/shm_limits.h>
#include <glibtop/msg_limits.h>
#include <glibtop/sem_limits.h>
#include <glibtop/proclist.h>

#include <glibtop/procstate.h>
#include <glibtop/procuid.h>
#include <glibtop/procmem.h>
#include <glibtop/proctime.h>
#include <glibtop/procsignal.h>
#include <glibtop/prockernel.h>
#include <glibtop/procsegment.h>

__BEGIN_DECLS

typedef union _glibtop_union	glibtop_union;

union _glibtop_union
{
	glibtop_cpu		cpu;
	glibtop_mem		mem;
	glibtop_swap		swap;
	glibtop_uptime		uptime;
	glibtop_loadavg		loadavg;
	glibtop_shm_limits	shm_limits;
	glibtop_msg_limits	msg_limits;
	glibtop_sem_limits	sem_limits;
	glibtop_proclist	proclist;
	glibtop_proc_state	proc_state;
	glibtop_proc_uid	proc_uid;
	glibtop_proc_mem	proc_mem;
	glibtop_proc_time	proc_time;
	glibtop_proc_signal	proc_signal;
	glibtop_proc_kernel	proc_kernel;
	glibtop_proc_segment	proc_segment;
};

__END_DECLS

#endif
