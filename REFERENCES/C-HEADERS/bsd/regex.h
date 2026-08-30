#define	ESIZE	512
#define	NBRA	9

struct regex {
    char expbuf[ESIZE];
    const char *braslist[NBRA];
    const char *braelist[NBRA];
    char circf;
    const char *start, *end;	/* pointers to occurrence in 's' */
};

extern const char *re_comp(const char *string);
extern int re_exec(const char *string);
extern int recmp(const char *pattern, const char *target);
extern struct regex *re_compile(const char *string, int fold);
extern int re_match(const char *string, struct regex *r);
