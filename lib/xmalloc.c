/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 4 -*- */

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

#include <glibtop/xmalloc.h>

#ifdef LIBGTOP_USE_GLIB_MALLOC
#include <glib.h>
#endif

/* Wrappers to malloc, calloc, realloc ... */

void *
glibtop_malloc_r (glibtop_server *server, size_t size)
{
#ifdef LIBGTOP_USE_GLIB_MALLOC
    return g_malloc0 (size);
#else
    void *buf = malloc (size);
	
    if (!buf)
	glibtop_error_io_r (server, "malloc %d bytes", size);
	
    return buf;
#endif
}

void *
glibtop_calloc_r (glibtop_server *server, size_t nmemb, size_t size)
{
#ifdef LIBGTOP_USE_GLIB_MALLOC
    return g_malloc0 (size * nmemb);
#else
    void *buf = calloc (nmemb, size);
	
    if (!buf)
	glibtop_error_io_r (server, "calloc %d blocks (%d bytes each)",
			    nmemb, size);
	
    return buf;
#endif
}

void *
glibtop_realloc_r (glibtop_server *server, void *ptr, size_t size)
{
#ifdef LIBGTOP_USE_GLIB_MALLOC
    return g_realloc (ptr, size);
#else
    void *buf = realloc (ptr, size);
	
    if (!buf)
	glibtop_error_io_r (server, "realloc %d bytes", size);
	
    return buf;
#endif
}

char *
glibtop_strdup_r (glibtop_server *server, const char *string)
{
#ifdef LIBGTOP_USE_GLIB_MALLOC
    return g_strdup (string);
#else
    return strcpy (glibtop_malloc_r (server, strlen (string) + 1), string);
#endif
}

void
glibtop_free_r (glibtop_server *server, const void *ptr)
{
#ifdef LIBGTOP_USE_GLIB_MALLOC
    g_free (ptr);
#else
    if (ptr) free ((void *) ptr);
#endif
}