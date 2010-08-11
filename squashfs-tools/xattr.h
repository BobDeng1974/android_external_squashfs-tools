/*
 * Create a squashfs filesystem.  This is a highly compressed read only
 * filesystem.
 *
 * Copyright (c) 2010
 * Phillip Lougher <phillip@lougher.demon.co.uk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * xattr.h
 */

#define XATTR_VALUE_OOL		SQUASHFS_XATTR_VALUE_OOL
#define XATTR_PREFIX_MASK	SQUASHFS_XATTR_PREFIX_MASK

#define XATTR_VALUE_OOL_SIZE	sizeof(long long)
#define XATTR_NAME_OOL_SIZE 	0 /* XXX dummy value */

#define XATTR_INLINE_MAX 	128
#define XATTR_NAME_INLINE_MAX	65536

#define XATTR_TARGET_MAX	65536

#define IS_XATTR(a)		(a != SQUASHFS_INVALID_XATTR)

struct xattr_list {
	char			*name;
	char			*full_name;
	int			size;
	int			vsize;
	void			*value;
	int			type;
	long long		ool_value;
	unsigned short		vchecksum;
	struct xattr_list	*vnext;
};

struct dupl_id {
	struct xattr_list	*xattr_list;
	int			xattrs;
	int			xattr_id;
	struct dupl_id		*next;
};

struct prefix {
	char			*prefix;
	int			type;
};

extern int generate_xattrs(int, struct xattr_list *);

#ifdef XATTR_SUPPORT
extern int get_xattrs(int, squashfs_super_block *);
extern int read_xattrs(void *);
extern long long write_xattrs();
extern int save_xattrs();
extern void restore_xattrs();
extern unsigned int xattr_bytes, total_xattr_bytes;
extern void write_xattr(char *, unsigned int);
extern int read_xattrs_from_disk(int, squashfs_super_block *);
extern struct xattr_list *get_xattr(int, unsigned int *);
#else
static inline int get_xattrs(int fd, squashfs_super_block *sBlk)
{
	if(sBlk->xattr_id_table_start != SQUASHFS_INVALID_BLK) {
		fprintf(stderr, "Xattrs in filesystem! These are not supported in this "
			"version of Squashfs\n");
		return 0;
	} else
		return SQUASHFS_INVALID_BLK;
}


static inline int read_xattrs(void *dir_ent)
{
	return SQUASHFS_INVALID_XATTR;
}


static inline long long write_xattrs()
{
	return SQUASHFS_INVALID_BLK;
}


static inline int save_xattrs()
{
	return 1;
}


static inline void restore_xattrs()
{
}


static inline void write_xattr(char *pathname, unsigned int xattr)
{
}


static inline int read_xattrs_from_disk(int fd, squashfs_super_block *sBlk)
{
	if(sBlk->xattr_id_table_start != SQUASHFS_INVALID_BLK) {
		fprintf(stderr, "Xattrs in filesystem! These are not supported in this "
			"version of Squashfs\n");
		return 0;
	} else
		return SQUASHFS_INVALID_BLK;
}


static inline struct xattr_list *get_xattr(int i, unsigned int *count)
{
	return NULL;
}
#endif
