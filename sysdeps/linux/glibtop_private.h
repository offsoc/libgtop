/* Copyright (C) 2004 Benoît Dejean
   This file is part of LibGTop 2.0.

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

#ifndef __LINUX__GLIBTOP_PRIVATE_H__
#define __LINUX__GLIBTOP_PRIVATE_H__

#include <glibtop.h>

#include <glib.h>

#include <fcntl.h>
#include <ctype.h>
#include <string.h>

G_BEGIN_DECLS

#define LINUX_VERSION_CODE(x,y,z)   (0x10000*(x) + 0x100*(y) + z)


static inline char*
next_token(const char *p)
{
	while (isspace(*p)) p++;
	return (char*) p;
}

static inline char *
skip_token (const char *p)
{
	p = next_token(p);
	while (*p && !isspace(*p)) p++;
	p = next_token(p);
	return (char *)p;
}

static inline char *
skip_multiple_token (const char *p, size_t count)
{
	while(count--)
		p = skip_token (p);

	return (char *)p;
}


static inline char *
skip_line (const char *p)
{
	while (*p && *p != '\n') p++;
	return (char *) (*p ? p+1 : p);
}


unsigned long long
get_scaled(const char *buffer, const char *key);


/* aborts on error */
void
file_to_buffer(glibtop *server, char *buffer, const char *filename);

/* return < 0 on error, otherwise 0 on success */
int
try_file_to_buffer(char *buffer, const char *format, ...);


/* some inline functions that wrap proc path
 * as fast as macros :)
 */

static inline int
proc_file_to_buffer (char *buffer, const char *fmt, pid_t pid)
{
	return try_file_to_buffer(buffer, fmt, pid);
}

static inline int
proc_stat_to_buffer (char *buffer, pid_t pid)
{
	return proc_file_to_buffer (buffer, "/proc/%d/stat", pid);
}

static inline int
proc_status_to_buffer (char *buffer, pid_t pid)
{
	return proc_file_to_buffer (buffer, "/proc/%d/status", pid);
}

static inline int
proc_statm_to_buffer (char *buffer, pid_t pid)
{
	return proc_file_to_buffer (buffer, "/proc/%d/statm", pid);
}


static inline char *
proc_stat_after_cmd (char *p)
{
	p = strrchr (p, ')');
	if (G_LIKELY(p))
		*p++ = '\0';
	return p;
}
G_END_DECLS

#endif /* __LINUX__GLIBTOP_PRIVATE_H__ */