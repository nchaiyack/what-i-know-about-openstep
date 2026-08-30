/*
 * Definitions of type tags used in NeXTime movie representation.
 *
 */

/*
 * Generic encoding type tag.  This contains a 4 byte value, with
 * each byte usually representing an ASCII character.
 */
typedef unsigned long NTTypeTag;
typedef unsigned char NTTypeName[5];

/*
 * An ugly macro to generate the type from 4 characters.  If your tag
 * uses less than 4 chars, pad it using space characters.  This macro generates
 * a constant, and so is useful for building case switches.
 */
#define NT_TYPE_TAG_VALUE( a, b, c, d )	\
	(((a) << 24) | ((b) << 16) | ((c) << 8) | (d))


/*
 * The following functions provide for conversions between the NTTypeName and
 * the NTTypeTag.
 */
static inline NTTypeTag NTTagFromName( const NTTypeName name )
{
	return ( NT_TYPE_TAG_VALUE(name[0], name[1], name[2], name[3]) );
}

static inline void NTNameFromTag( NTTypeTag type, NTTypeName name )
{
	name[0] = (type >> 24) & 0xFF;
	name[1] = (type >> 16) & 0xFF;
	name[2] = (type >> 8) & 0xFF;
	name[3] = type & 0xFF;
	name[4] = '\0';
}

/*
 * Basic system-wide NTTypeTag value definitions
 */
#define NT_TYPE_TAG_UNDEFINED		((NTTypeTag)0)
#define NT_TYPE_TAG_MOVIE_RSRC		NT_TYPE_TAG_VALUE('m','o','o','v')
#define NT_TYPE_TAG_MOVIE_DATA		NT_TYPE_TAG_VALUE('m','d','a','t')
#define NT_TYPE_TAG_SKIP		NT_TYPE_TAG_VALUE('s','k','i','p')
#define NT_TYPE_TAG_MOVIE		NT_TYPE_TAG_VALUE('m','o','o','v')
#define NT_TYPE_TAG_MOVIE_HEADER	NT_TYPE_TAG_VALUE('m','v','h','d')
#define NT_TYPE_TAG_TRACK		NT_TYPE_TAG_VALUE('t','r','a','k')
#define NT_TYPE_TAG_TRACK_HEADER	NT_TYPE_TAG_VALUE('t','k','h','d')
#define NT_TYPE_TAG_CLIP		NT_TYPE_TAG_VALUE('c','l','i','p')
#define NT_TYPE_TAG_CLIP_REGION		NT_TYPE_TAG_VALUE('c','r','g','n')
#define NT_TYPE_TAG_MATTE		NT_TYPE_TAG_VALUE('m','a','t','t')
#define NT_TYPE_TAG_COMPRESSED_MATTE	NT_TYPE_TAG_VALUE('k','m','a','t')
#define NT_TYPE_TAG_EDITS		NT_TYPE_TAG_VALUE('e','d','t','s')
#define NT_TYPE_TAG_EDIT_LIST		NT_TYPE_TAG_VALUE('e','l','s','t')
#define NT_TYPE_TAG_MEDIA		NT_TYPE_TAG_VALUE('m','d','i','a')
#define NT_TYPE_TAG_MEDIA_HEADER	NT_TYPE_TAG_VALUE('m','d','h','d')
#define NT_TYPE_TAG_MEDIA_INFO		NT_TYPE_TAG_VALUE('m','i','n','f')
#define NT_TYPE_TAG_VIDEO_MEDIA_INFO	NT_TYPE_TAG_VALUE('v','m','h','d')
#define NT_TYPE_TAG_SOUND_MEDIA_INFO	NT_TYPE_TAG_VALUE('s','m','h','d')
#define NT_TYPE_TAG_GENERIC_MEDIA_INFO	NT_TYPE_TAG_VALUE('g','m','h','d')
#define NT_TYPE_TAG_GENERIC_INFO	NT_TYPE_TAG_VALUE('g','m','i','n')
#define NT_TYPE_TAG_DATA_INFO		NT_TYPE_TAG_VALUE('d','i','n','f')
#define NT_TYPE_TAG_DATA_REFERENCE	NT_TYPE_TAG_VALUE('d','r','e','f')
#define NT_TYPE_TAG_DATA_ALIAS		NT_TYPE_TAG_VALUE('a','l','i','s')
#define NT_TYPE_TAG_DATA_UNIX		NT_TYPE_TAG_VALUE('U','n','i','x')
#define NT_TYPE_TAG_SAMPLE_TABLE	NT_TYPE_TAG_VALUE('s','t','b','l')
#define NT_TYPE_TAG_SAMPLE_DESC		NT_TYPE_TAG_VALUE('s','t','s','d')
#define NT_TYPE_TAG_SAMPLE_SIZE		NT_TYPE_TAG_VALUE('s','t','s','z')
#define NT_TYPE_TAG_TIME_TO_SAMPLE	NT_TYPE_TAG_VALUE('s','t','t','s')
#define NT_TYPE_TAG_SYNC_SAMPLE		NT_TYPE_TAG_VALUE('s','t','s','s')
#define NT_TYPE_TAG_SHADOW_SYNC		NT_TYPE_TAG_VALUE('s','t','s','h')
#define NT_TYPE_TAG_SAMPLE_TO_CHUNK	NT_TYPE_TAG_VALUE('s','t','s','c')
#define NT_TYPE_TAG_CHUNK_OFFSET	NT_TYPE_TAG_VALUE('s','t','c','o')
#define NT_TYPE_TAG_HANDLER_REFERENCE	NT_TYPE_TAG_VALUE('h','d','l','r')

#define NT_TYPE_TAG_VIDEO		NT_TYPE_TAG_VALUE('v','i','d','e')
#define NT_TYPE_TAG_SOUND		NT_TYPE_TAG_VALUE('s','o','u','n')
#define NT_TYPE_TAG_TEXT		NT_TYPE_TAG_VALUE('t','e','x','t')

/*
 * NeXT extension - Tag used within 'alis' atom to denote a Unix filename
 * as an external data reference.
 */
#define NT_TYPE_TAG_UNIX_FILE		NT_TYPE_TAG_VALUE('U','X','f','i')

/*
 * Tags used in NTUserData representations
 */
#define NT_TYPE_TAG_USERDATA		NT_TYPE_TAG_VALUE('u','d','t','a')
#define NT_TYPE_TAG_COPYRIGHT		NT_TYPE_TAG_VALUE (0xa9,'c','p','y')
#define NT_TAG_TYPE_DATE		NT_TYPE_TAG_VALUE (0xa9,'d','a','y')
#define NT_TAG_TYPE_DIRECTOR		NT_TYPE_TAG_VALUE (0xa9,'d','i','r')
#define NT_TAG_TYPE_EDIT_DESC1		NT_TYPE_TAG_VALUE (0xa9,'e','d','1')
#define NT_TAG_TYPE_EDIT_DESC2		NT_TYPE_TAG_VALUE (0xa9,'e','d','2')
#define NT_TAG_TYPE_EDIT_DESC3		NT_TYPE_TAG_VALUE (0xa9,'e','d','3')
#define NT_TAG_TYPE_EDIT_DESC4		NT_TYPE_TAG_VALUE (0xa9,'e','d','4')
#define NT_TAG_TYPE_EDIT_DESC5		NT_TYPE_TAG_VALUE (0xa9,'e','d','5')
#define NT_TAG_TYPE_EDIT_DESC6		NT_TYPE_TAG_VALUE (0xa9,'e','d','6')
#define NT_TAG_TYPE_EDIT_DESC7		NT_TYPE_TAG_VALUE (0xa9,'e','d','7')
#define NT_TAG_TYPE_EDIT_DESC8		NT_TYPE_TAG_VALUE (0xa9,'e','d','8')
#define NT_TAG_TYPE_EDIT_DESC9		NT_TYPE_TAG_VALUE (0xa9,'e','d','9')
#define NT_TAG_TYPE_FORMAT		NT_TYPE_TAG_VALUE (0xa9,'f','m','t')
#define NT_TAG_TYPE_INFORMATION		NT_TYPE_TAG_VALUE (0xa9,'i','n','f')
#define NT_TAG_TYPE_PRODUCER		NT_TYPE_TAG_VALUE (0xa9,'p','r','d')
#define NT_TAG_TYPE_PERFORMERS		NT_TYPE_TAG_VALUE (0xa9,'p','r','f')
#define NT_TAG_TYPE_REQUIREMENTS	NT_TYPE_TAG_VALUE (0xa9,'r','e','q')
#define NT_TAG_TYPE_SOURCE_CREDITS	NT_TYPE_TAG_VALUE (0xa9,'s','r','c')
#define NT_TAG_TYPE_WRITERS		NT_TYPE_TAG_VALUE (0xa9,'w','r','t')
