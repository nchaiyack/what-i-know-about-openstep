/*	pwd.h	4.1	83/05/03	*/
/* Copyright (c) 1992, NeXT Computer, Inc. */

#ifndef _PWD_H
#define	_PWD_H

#include <standards.h>

#ifdef _POSIX_SOURCE
	#include <sys/types.h>		/* for uid_t */
#endif /* _POSIX_SOURCE */

#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	struct	passwd {	/* see getpwent(3) */
		char	*pw_name;
		char	*pw_passwd;
	#ifdef _POSIX_SOURCE
	    #if defined(__BIG_ENDIAN__)
		short	pw_short_pad1;	/* pad to preserve struct size */
		uid_t	pw_uid;
		short	pw_short_pad2;	/* pad to preserve struct size */
		gid_t	pw_gid;
	    #else
		uid_t	pw_uid;
		short	pw_short_pad1;	/* pad to preserve struct size */
		gid_t	pw_gid;
		short	pw_short_pad2;	/* pad to preserve struct size */
	    #endif
	#else
		int	pw_uid;
		int	pw_gid;
	#endif /* _POSIX_SOURCE */
		int	pw_quota;
		char	*pw_comment;
		char	*pw_gecos;
		char	*pw_dir;
		char	*pw_shell;
	};
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

	#ifdef _POSIX_SOURCE
		#ifdef __STDC__
			struct passwd *getpwuid(uid_t uid); 		 
			struct passwd *getpwnam(const char *name);
		#else
			struct passwd *getpwuid(); 
			struct passwd *getpwnam();
		#endif /* __STDC__ */
	#else
		#ifdef __STRICT_BSD__
			struct passwd *getpwent();
			struct passwd *getpwuid();
			struct passwd *getpwnam();
		#else
			struct passwd *getpwuid(int uid);
			struct passwd *getpwnam(const char *name);
			struct passwd *getpwent(void);
			void endpwent(void);
			void setpwent(void);
		#endif /* __STRICT_BSD__ */
	#endif /* _POSIX_SOURCE */
#endif /* _PWD_H */
