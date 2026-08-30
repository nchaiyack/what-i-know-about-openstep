/*
 * Lookup protocol definitions - internal to NeXT
 * Copyright (C) 1989 by NeXT, Inc.
 */

/*
 * the port to lookupd is obtained through the (internal)
 * _lookupd_port() syscall instead of through the nameserver
 * with LOOKUP_SERVER_NAME as "C Library Lookup"
 */

#define UNIT_SIZE 4

typedef struct unit {
	char data[UNIT_SIZE];
} unit;

#define MAX_INLINE_UNITS 2047
#define MAX_LOOKUP_NAMELEN 256
#define MAX_INLINE_DATA (MAX_INLINE_UNITS * sizeof(unit))

typedef char lookup_name[MAX_LOOKUP_NAMELEN];
typedef unit inline_data[MAX_INLINE_UNITS];
typedef char *ooline_data;
