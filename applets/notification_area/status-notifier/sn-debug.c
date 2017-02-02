/*
 * Copyright (C) 2017 Colomban Wendling <cwendling@hypra.fr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include "sn-debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define LOGFILE "/tmp/sn.log"

static FILE *sn_logfile__ = NULL;

static void
sn_logfile_cleanup (void)
{
  if (sn_logfile__)
    {
      fclose (sn_logfile__);
      sn_logfile__ = NULL;
    }
}

static FILE *
sn_logfile (void)
{
  if (! sn_logfile__)
    {
      sn_logfile__ = fopen (LOGFILE, "wb");
      setvbuf (sn_logfile__, NULL, _IONBF, 0);
      atexit (sn_logfile_cleanup);
    }
  return sn_logfile__;
}

void
sn_debug (const char *fmt,
          ...)
{
  va_list ap;
  
  va_start (ap, fmt);
  vfprintf (sn_logfile (), fmt, ap);
  va_end (ap);
}
