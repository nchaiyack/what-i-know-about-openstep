/*
 * Output of the RPC protocol compiler: DO NOT EDIT
 * Copyright (C) 1989 by NeXT, Inc.
 */
#define NI_NAME_MAXLEN 65535
#define NI_NAMELIST_MAXLEN 65535
#define NI_PROPLIST_MAXLEN 65535
#define NI_IDLIST_MAXLEN 1048576
typedef unsigned long ni_index;

struct ni_id {
	u_long nii_object;
	u_long nii_instance;
};
typedef struct ni_id ni_id;
bool_t xdr_ni_id();


typedef char *ni_name;
bool_t xdr_ni_name();


typedef struct {
	u_int ni_namelist_len;
	ni_name *ni_namelist_val;
} ni_namelist;
bool_t xdr_ni_namelist();


struct ni_property {
	ni_name nip_name;
	ni_namelist nip_val;
};
typedef struct ni_property ni_property;
bool_t xdr_ni_property();


typedef struct {
	u_int ni_proplist_len;
	ni_property *ni_proplist_val;
} ni_proplist;
bool_t xdr_ni_proplist();


typedef struct {
	u_int ni_idlist_len;
	u_long *ni_idlist_val;
} ni_idlist;
bool_t xdr_ni_idlist();


struct ni_object {
	ni_id nio_id;
	ni_proplist nio_props;
	u_long nio_parent;
	ni_idlist nio_children;
};
typedef struct ni_object ni_object;
bool_t xdr_ni_object();


enum ni_status {
	NI_OK = 0,
	NI_BADID = 1,
	NI_STALE = 2,
	NI_NOSPACE = 3,
	NI_PERM = 4,
	NI_NODIR = 5,
	NI_NOPROP = 6,
	NI_NONAME = 7,
	NI_NOTEMPTY = 8,
	NI_UNRELATED = 9,
	NI_SERIAL = 10,
	NI_NETROOT = 11,
	NI_NORESPONSE = 12,
	NI_RDONLY = 13,
	NI_SYSTEMERR = 14,
	NI_ALIVE = 15,
	NI_NOTMASTER = 16,
	NI_CANTFINDADDRESS = 17,
	NI_DUPTAG = 18,
	NI_NOTAG = 19,
	NI_AUTHERROR = 20,
	NI_NOUSER = 21,
	NI_MASTERBUSY = 22,
	NI_INVALIDDOMAIN = 23,
	NI_BADOP = 24,
	NI_FAILED = 9999,
};
typedef enum ni_status ni_status;
bool_t xdr_ni_status();


struct ni_id_res {
	ni_status status;
	union {
		ni_id id;
	} ni_id_res_u;
};
typedef struct ni_id_res ni_id_res;
bool_t xdr_ni_id_res();


struct ni_parent_stuff {
	u_long object_id;
	ni_id self_id;
};
typedef struct ni_parent_stuff ni_parent_stuff;
bool_t xdr_ni_parent_stuff();


struct ni_parent_res {
	ni_status status;
	union {
		struct ni_parent_stuff stuff;
	} ni_parent_res_u;
};
typedef struct ni_parent_res ni_parent_res;
bool_t xdr_ni_parent_res();


struct ni_children_stuff {
	ni_idlist children;
	ni_id self_id;
};
typedef struct ni_children_stuff ni_children_stuff;
bool_t xdr_ni_children_stuff();


struct ni_children_res {
	ni_status status;
	union {
		ni_children_stuff stuff;
	} ni_children_res_u;
};
typedef struct ni_children_res ni_children_res;
bool_t xdr_ni_children_res();


struct ni_entry {
	u_long id;
	ni_namelist *names;
};
typedef struct ni_entry ni_entry;
bool_t xdr_ni_entry();


typedef struct {
	u_int ni_entrylist_len;
	ni_entry *ni_entrylist_val;
} ni_entrylist;
bool_t xdr_ni_entrylist();


struct ni_list_stuff {
	ni_entrylist entries;
	ni_id self_id;
};
typedef struct ni_list_stuff ni_list_stuff;
bool_t xdr_ni_list_stuff();


struct ni_list_res {
	ni_status status;
	union {
		ni_list_stuff stuff;
	} ni_list_res_u;
};
typedef struct ni_list_res ni_list_res;
bool_t xdr_ni_list_res();


struct ni_proplist_stuff {
	ni_id id;
	ni_proplist props;
};
typedef struct ni_proplist_stuff ni_proplist_stuff;
bool_t xdr_ni_proplist_stuff();


struct ni_create_args {
	ni_id id;
	ni_proplist props;
	u_long where;
	ni_id *target_id;
};
typedef struct ni_create_args ni_create_args;
bool_t xdr_ni_create_args();


struct ni_proplist_res {
	ni_status status;
	union {
		ni_proplist_stuff stuff;
	} ni_proplist_res_u;
};
typedef struct ni_proplist_res ni_proplist_res;
bool_t xdr_ni_proplist_res();


struct ni_create_stuff {
	ni_id id;
	ni_id self_id;
};
typedef struct ni_create_stuff ni_create_stuff;
bool_t xdr_ni_create_stuff();


struct ni_create_res {
	ni_status status;
	union {
		ni_create_stuff stuff;
	} ni_create_res_u;
};
typedef struct ni_create_res ni_create_res;
bool_t xdr_ni_create_res();


struct ni_destroy_args {
	ni_id parent_id;
	ni_id self_id;
};
typedef struct ni_destroy_args ni_destroy_args;
bool_t xdr_ni_destroy_args();


struct ni_lookup_args {
	ni_id id;
	ni_name key;
	ni_name value;
};
typedef struct ni_lookup_args ni_lookup_args;
bool_t xdr_ni_lookup_args();


struct ni_lookup_stuff {
	ni_idlist idlist;
	ni_id self_id;
};
typedef struct ni_lookup_stuff ni_lookup_stuff;
bool_t xdr_ni_lookup_stuff();


struct ni_lookup_res {
	ni_status status;
	union {
		ni_lookup_stuff stuff;
	} ni_lookup_res_u;
};
typedef struct ni_lookup_res ni_lookup_res;
bool_t xdr_ni_lookup_res();


struct ni_name_args {
	ni_id id;
	ni_name name;
};
typedef struct ni_name_args ni_name_args;
bool_t xdr_ni_name_args();


struct ni_createprop_args {
	ni_id id;
	ni_property prop;
	u_long where;
};
typedef struct ni_createprop_args ni_createprop_args;
bool_t xdr_ni_createprop_args();


struct ni_writeprop_args {
	ni_id id;
	u_long prop_index;
	ni_namelist values;
};
typedef struct ni_writeprop_args ni_writeprop_args;
bool_t xdr_ni_writeprop_args();


struct ni_prop_args {
	ni_id id;
	u_long prop_index;
};
typedef struct ni_prop_args ni_prop_args;
bool_t xdr_ni_prop_args();


struct ni_namelist_stuff {
	ni_namelist values;
	ni_id self_id;
};
typedef struct ni_namelist_stuff ni_namelist_stuff;
bool_t xdr_ni_namelist_stuff();


struct ni_namelist_res {
	ni_status status;
	union {
		ni_namelist_stuff stuff;
	} ni_namelist_res_u;
};
typedef struct ni_namelist_res ni_namelist_res;
bool_t xdr_ni_namelist_res();


struct ni_propname_args {
	ni_id id;
	u_long prop_index;
	ni_name name;
};
typedef struct ni_propname_args ni_propname_args;
bool_t xdr_ni_propname_args();


struct ni_createname_args {
	ni_id id;
	u_long prop_index;
	ni_name name;
	u_long where;
};
typedef struct ni_createname_args ni_createname_args;
bool_t xdr_ni_createname_args();


struct ni_nameindex_args {
	ni_id id;
	u_long prop_index;
	u_long name_index;
};
typedef struct ni_nameindex_args ni_nameindex_args;
bool_t xdr_ni_nameindex_args();


struct ni_writename_args {
	ni_id id;
	u_long prop_index;
	u_long name_index;
	ni_name name;
};
typedef struct ni_writename_args ni_writename_args;
bool_t xdr_ni_writename_args();


struct ni_readname_stuff {
	ni_id id;
	ni_name name;
};
typedef struct ni_readname_stuff ni_readname_stuff;
bool_t xdr_ni_readname_stuff();


struct ni_readname_res {
	ni_status status;
	union {
		ni_readname_stuff stuff;
	} ni_readname_res_u;
};
typedef struct ni_readname_res ni_readname_res;
bool_t xdr_ni_readname_res();


struct ni_binding {
	ni_name tag;
	u_int addr;
};
typedef struct ni_binding ni_binding;
bool_t xdr_ni_binding();


struct ni_rparent_res {
	ni_status status;
	union {
		ni_binding binding;
	} ni_rparent_res_u;
};
typedef struct ni_rparent_res ni_rparent_res;
bool_t xdr_ni_rparent_res();


typedef struct ni_object_node *ni_object_list;
bool_t xdr_ni_object_list();


struct ni_object_node {
	ni_object object;
	ni_object_list next;
};
typedef struct ni_object_node ni_object_node;
bool_t xdr_ni_object_node();


struct ni_readall_stuff {
	u_int checksum;
	u_long highestid;
	ni_object_list list;
};
typedef struct ni_readall_stuff ni_readall_stuff;
bool_t xdr_ni_readall_stuff();


struct ni_readall_res {
	ni_status status;
	union {
		ni_readall_stuff stuff;
	} ni_readall_res_u;
};
typedef struct ni_readall_res ni_readall_res;
bool_t xdr_ni_readall_res();


typedef struct {
	u_int ni_proplist_list_len;
	ni_proplist *ni_proplist_list_val;
} ni_proplist_list;
bool_t xdr_ni_proplist_list();


struct ni_listall_stuff {
	ni_id self_id;
	ni_proplist_list entries;
};
typedef struct ni_listall_stuff ni_listall_stuff;
bool_t xdr_ni_listall_stuff();


struct ni_listall_res {
	ni_status status;
	union {
		ni_listall_stuff stuff;
	} ni_listall_res_u;
};
typedef struct ni_listall_res ni_listall_res;
bool_t xdr_ni_listall_res();


#define NI_PROG ((u_long)200100000)
#define NI_VERS ((u_long)2)
#define _NI_PING ((u_long)0)
extern void *_ni_ping_2();
#define _NI_STATISTICS ((u_long)1)
extern ni_proplist *_ni_statistics_2();
#define _NI_ROOT ((u_long)2)
extern ni_id_res *_ni_root_2();
#define _NI_SELF ((u_long)3)
extern ni_id_res *_ni_self_2();
#define _NI_PARENT ((u_long)4)
extern ni_parent_res *_ni_parent_2();
#define _NI_CREATE ((u_long)5)
extern ni_create_res *_ni_create_2();
#define _NI_DESTROY ((u_long)6)
extern ni_id_res *_ni_destroy_2();
#define _NI_READ ((u_long)7)
extern ni_proplist_res *_ni_read_2();
#define _NI_WRITE ((u_long)8)
extern ni_id_res *_ni_write_2();
#define _NI_CHILDREN ((u_long)9)
extern ni_children_res *_ni_children_2();
#define _NI_LOOKUP ((u_long)10)
extern ni_lookup_res *_ni_lookup_2();
#define _NI_LIST ((u_long)11)
extern ni_list_res *_ni_list_2();
#define _NI_CREATEPROP ((u_long)12)
extern ni_id_res *_ni_createprop_2();
#define _NI_DESTROYPROP ((u_long)13)
extern ni_id_res *_ni_destroyprop_2();
#define _NI_READPROP ((u_long)14)
extern ni_namelist_res *_ni_readprop_2();
#define _NI_WRITEPROP ((u_long)15)
extern ni_id_res *_ni_writeprop_2();
#define _NI_RENAMEPROP ((u_long)16)
extern ni_id_res *_ni_renameprop_2();
#define _NI_LISTPROPS ((u_long)17)
extern ni_namelist_res *_ni_listprops_2();
#define _NI_CREATENAME ((u_long)18)
extern ni_id_res *_ni_createname_2();
#define _NI_DESTROYNAME ((u_long)19)
extern ni_id_res *_ni_destroyname_2();
#define _NI_READNAME ((u_long)20)
extern ni_readname_res *_ni_readname_2();
#define _NI_WRITENAME ((u_long)21)
extern ni_id_res *_ni_writename_2();
#define _NI_RPARENT ((u_long)22)
extern ni_rparent_res *_ni_rparent_2();
#define _NI_LISTALL ((u_long)23)
extern ni_listall_res *_ni_listall_2();
#define _NI_BIND ((u_long)24)
extern void *_ni_bind_2();
#define _NI_READALL ((u_long)25)
extern ni_readall_res *_ni_readall_2();
#define _NI_CRASHED ((u_long)26)
extern void *_ni_crashed_2();
#define _NI_RESYNC ((u_long)27)
extern ni_status *_ni_resync_2();
#define _NI_LOOKUPREAD ((u_long)28)
extern ni_proplist_res *_ni_lookupread_2();

