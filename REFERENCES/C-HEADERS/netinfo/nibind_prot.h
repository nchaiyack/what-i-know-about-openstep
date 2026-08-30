/*
 * Output of the RPC protocol compiler: DO NOT EDIT
 * Copyright (C) 1989 by NeXT, Inc.
 */
#ifndef NI_PROG
#include <netinfo/ni_prot.h>
#endif
#define NIBIND_MAXREGS 32

struct nibind_addrinfo {
	u_int udp_port;
	u_int tcp_port;
};
typedef struct nibind_addrinfo nibind_addrinfo;
bool_t xdr_nibind_addrinfo();


struct nibind_registration {
	ni_name tag;
	nibind_addrinfo addrs;
};
typedef struct nibind_registration nibind_registration;
bool_t xdr_nibind_registration();


struct nibind_getregister_res {
	ni_status status;
	union {
		nibind_addrinfo addrs;
	} nibind_getregister_res_u;
};
typedef struct nibind_getregister_res nibind_getregister_res;
bool_t xdr_nibind_getregister_res();


struct nibind_listreg_res {
	ni_status status;
	union {
		struct {
			u_int regs_len;
			nibind_registration *regs_val;
		} regs;
	} nibind_listreg_res_u;
};
typedef struct nibind_listreg_res nibind_listreg_res;
bool_t xdr_nibind_listreg_res();


struct nibind_clone_args {
	ni_name tag;
	ni_name master_name;
	u_int master_addr;
	ni_name master_tag;
};
typedef struct nibind_clone_args nibind_clone_args;
bool_t xdr_nibind_clone_args();


struct nibind_bind_args {
	u_int client_addr;
	ni_name client_tag;
	ni_name server_tag;
};
typedef struct nibind_bind_args nibind_bind_args;
bool_t xdr_nibind_bind_args();


#define NIBIND_PROG ((u_long)200100001)
#define NIBIND_VERS ((u_long)1)
#define NIBIND_PING ((u_long)0)
extern void *nibind_ping_1();
#define NIBIND_REGISTER ((u_long)1)
extern ni_status *nibind_register_1();
#define NIBIND_UNREGISTER ((u_long)2)
extern ni_status *nibind_unregister_1();
#define NIBIND_GETREGISTER ((u_long)3)
extern nibind_getregister_res *nibind_getregister_1();
#define NIBIND_LISTREG ((u_long)4)
extern nibind_listreg_res *nibind_listreg_1();
#define NIBIND_CREATEMASTER ((u_long)5)
extern ni_status *nibind_createmaster_1();
#define NIBIND_CREATECLONE ((u_long)6)
extern ni_status *nibind_createclone_1();
#define NIBIND_DESTROYDOMAIN ((u_long)7)
extern ni_status *nibind_destroydomain_1();
#define NIBIND_BIND ((u_long)8)
extern void *nibind_bind_1();

