/* $Id$ */

/* Copyright (C) 1998-99 Martin Baulig
   This file is part of LibGTop 1.0.

   Contributed by Martin Baulig <martin@home-of-linux.org>, April 1998.

   LibGTop is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License,
   or (at your option) any later version.

   LibGTop is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.

   You should have received a copy of the GNU General Public License
   along with LibGTop; see the file COPYING. If not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#include <glibtop.h>
#include <glibtop/error.h>
#include <glibtop/cpu.h>

static const unsigned long _glibtop_sysdeps_cpu =
(1 << GLIBTOP_CPU_TOTAL) + (1 << GLIBTOP_CPU_USER) +
(1 << GLIBTOP_CPU_SYS) + (1 << GLIBTOP_CPU_IDLE) +
(1 << GLIBTOP_XCPU_TOTAL) + (1 << GLIBTOP_XCPU_USER) +
(1 << GLIBTOP_XCPU_SYS) + (1 << GLIBTOP_XCPU_IDLE);

/* Init function. */

void
glibtop_init_cpu_s (glibtop *server)
{
    server->sysdeps.cpu = _glibtop_sysdeps_cpu;
}

/* Provides information about cpu usage. */

void
glibtop_get_cpu_s (glibtop *server, glibtop_cpu *buf)
{
    kstat_ctl_t *kc = server->machine.kc;
    cpu_stat_t cpu_stat;
    int cpu, ncpu;
    kid_t ret;

    memset (buf, 0, sizeof (glibtop_cpu));

    ncpu = server->ncpu;
    if (ncpu > GLIBTOP_NCPU) ncpu = GLIBTOP_NCPU;

    for (cpu = 0; cpu < ncpu; cpu++) {
	kstat_t *ksp = server->machine.cpu_stat_kstat [cpu];
	if (!ksp) continue;

	ret = kstat_read (kc, ksp, &cpu_stat);

	if (ret == -1) {
	    glibtop_warn_io_r (server, "kstat_read (cpu_stat%d)", cpu);
	    continue;
	}

	buf->xcpu_idle [cpu] = cpu_stat.cpu_sysinfo.cpu [CPU_IDLE];
	buf->xcpu_user [cpu] = cpu_stat.cpu_sysinfo.cpu [CPU_IDLE];
	buf->xcpu_sys [cpu] = cpu_stat.cpu_sysinfo.cpu [CPU_IDLE];

	buf->xcpu_total [cpu] = buf->xcpu_idle [cpu] + buf->xcpu_user [cpu] +
	    buf->xcpu_sys [cpu];

	buf->idle += cpu_stat.cpu_sysinfo.cpu [CPU_IDLE];
	buf->user += cpu_stat.cpu_sysinfo.cpu [CPU_USER];
	buf->sys  += cpu_stat.cpu_sysinfo.cpu [CPU_KERNEL];
    }

    buf->total = buf->idle + buf->user + buf->sys;

    buf->flags = _glibtop_sysdeps_cpu;
}