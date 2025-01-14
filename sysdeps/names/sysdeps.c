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
#include <glibtop/union.h>
#include <glibtop/sysdeps.h>

const char *glibtop_names_sysdeps [GLIBTOP_MAX_SYSDEPS] =
{
	"cpu", "mem", "swap", "uptime", "loadavg", "shm_limits",
	"msg_limits", "sem_limits", "proclist", "proc_state",
	"proc_uid", "proc_mem", "proc_time", "proc_signal",
	"proc_kernel", "proc_segment"
};

const char *glibtop_types_sysdeps [GLIBTOP_MAX_SYSDEPS] =
{
	"unsigned long", "unsigned long", "unsigned long", "unsigned long",
	"unsigned long", "unsigned long", "unsigned long", "unsigned long",
	"unsigned long", "unsigned long", "unsigned long", "unsigned long",
	"unsigned long", "unsigned long", "unsigned long", "unsigned long"
};

const char *glibtop_labels_sysdeps [GLIBTOP_MAX_SYSDEPS] =
{
	N_("CPU Usage"),
	N_("Memory Usage"),
	N_("Swap Usage"),
	N_("System Uptime"),
	N_("Load Averange"),
	N_("Shared Memory Limits"),
	N_("Message Queue Limits"),
	N_("Semaphore Set Limits"),
	N_("List of running Processes"),
	N_("Process Status information"),
	N_("Process UID and TTY information"),
	N_("Process Memory information"),
	N_("Process Time information"),
	N_("Process Signal information"),
	N_("Process Kernel Data information"),
	N_("Process Segment information")
};

const char *glibtop_descriptions_sysdeps [GLIBTOP_MAX_SYSDEPS] =
{
	N_("CPU Usage"),
	N_("Memory Usage"),
	N_("Swap Usage"),
	N_("System Uptime"),
	N_("Load Averange"),
	N_("Shared Memory Limits"),
	N_("Message Queue Limits"),
	N_("Semaphore Set Limits"),
	N_("List of running Processes"),
	N_("Process Status information"),
	N_("Process UID and TTY information"),
	N_("Process Memory information"),
	N_("Process Time information"),
	N_("Process Signal information"),
	N_("Process Kernel Data information"),
	N_("Process Segment information")
};
