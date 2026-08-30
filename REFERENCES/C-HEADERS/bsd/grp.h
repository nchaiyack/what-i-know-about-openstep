/*	grp.h	4.1	83/05/03	*/
/* Copyright (c) 1992, NeXT Computer, Inc. */

#ifndef _GRP_H
#define _GRP_H

#include <standards.h>

#ifdef _POSIX_SOURCE
	#include <sys/types.h>          /* for gid_t */
#endif /* _POSIX_SOURCE */

#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	struct	group { /* see getgrent(3) */
		char	*gr_name;
		char	*gr_passwd;
	#ifdef _POSIX_SOURCE
		short	gr_short_pad;	/* pad to preserve struct size */
		gid_t	gr_gid;
	#else
		int	gr_gid;
	#endif /* _POSIX_SOURCE */
		char	**gr_mem;
	};

	#ifdef _POSIX_SOURCE
		#ifdef __STDC__
			struct group *getgrgid(gid_t gid);
			struct group *getgrnam(const char *name);
		#else
			struct group *getgrgid();
			struct group *getgrnam();
		#endif /* __STDC__ */

	#elif defined(__STRICT_BSD__)
		struct group *getgrent(), *getgrgid(), *getgrnam();

	#elif defined(__STDC__)
		void setgrent(void);
		void endgrent(void);
		struct group *getgrent(void);
		struct group *getgrgid(int gid);
		struct group *getgrnam(const char *name);

	#else
		void setgrent();
		void endgrent();
		struct group *getgrent();
		struct group *getgrgid();
		struct group *getgrnam();

	#endif
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#endif  /* _GRP_H */
