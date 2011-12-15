/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2011 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/

#ifndef _SDL_config_nintendods_h
#define _SDL_config_nintendods_h

#include "SDL_platform.h"

/* This is a set of defines to configure the SDL features */

#if !defined(_STDINT_H_) && (!defined(HAVE_STDINT_H) || !_HAVE_STDINT_H)
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long long int64_t;
typedef unsigned long long uint64_t;

/* LiF: __PTRDIFF_TYPE__ was causing errors of conflicting typedefs with the
   <stdint.h> shipping with devkitARM.  copied a similar ifdef from it. */
#ifndef __PTRDIFF_TYPE__
typedef unsigned long uintptr_t;
#else
typedef unsigned __PTRDIFF_TYPE__ uintptr_t;
#endif
#endif /* !_STDINT_H_ && !HAVE_STDINT_H */

#define SIZEOF_VOIDP 4

/* Useful headers */
#define HAVE_SYS_TYPES_H	1
#define HAVE_STDIO_H	1
#define STDC_HEADERS	1
#define HAVE_STRING_H	1
#define HAVE_CTYPE_H	1

/* C library functions */
#define HAVE_MALLOC	1
#define HAVE_CALLOC	1
#define HAVE_REALLOC	1
#define HAVE_FREE	1
#define HAVE_ALLOCA	1
#define HAVE_GETENV	1
#define HAVE_SETENV	1
#define HAVE_PUTENV	1
#define HAVE_QSORT	1
#define HAVE_ABS	1
#define HAVE_BCOPY	1
#define HAVE_MEMSET	1
#define HAVE_MEMCPY	1
#define HAVE_MEMMOVE	1
#define HAVE_MEMCMP	1
#define HAVE_STRLEN	1
#define HAVE_STRDUP	1
#define HAVE_INDEX	1
#define HAVE_RINDEX	1
#define HAVE_STRCHR	1
#define HAVE_STRRCHR	1
#define HAVE_STRSTR	1
#define HAVE_STRTOL	1
#define HAVE_STRTOD	1
#define HAVE_ATOI	1
#define HAVE_ATOF	1
#define HAVE_STRCMP	1
#define HAVE_STRNCMP	1
#define HAVE_STRICMP	1
#define HAVE_STRCASECMP	1
#define HAVE_SSCANF	1
#define HAVE_SNPRINTF	1
#define HAVE_VSNPRINTF	1

/* DS isn't that sophisticated */
#define LACKS_SYS_MMAN_H 1

/* Enable various audio drivers */
#define SDL_AUDIO_DRIVER_NDS	1
/*#define SDL_AUDIO_DRIVER_DUMMY	1 TODO: uncomment this later*/

/* Enable various input drivers */
#define SDL_JOYSTICK_NDS	1
/*#define SDL_JOYSTICK_DUMMY	1 TODO: uncomment this later*/

/* DS has no dynamic linking afaik */
#define SDL_LOADSO_DISABLED	1

/* Enable various threading systems */
/*#define SDL_THREAD_NDS	1*/
#define SDL_THREADS_DISABLED	1

/* Enable various timer systems */
#define SDL_TIMER_NDS	1

/* Enable various video drivers */
#define SDL_VIDEO_DRIVER_NDS	1
#ifdef USE_HW_RENDERER
#define SDL_VIDEO_RENDER_NDS	1
#else
#define SDL_VIDEO_RENDER_NDS	0
#endif

/* Enable system power support */
#define SDL_POWER_NINTENDODS 1

/* Enable haptic support */
#define SDL_HAPTIC_NDS 1

#define SDL_BYTEORDER   SDL_LIL_ENDIAN

#endif /* _SDL_config_nintendods_h */