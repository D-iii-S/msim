/*
 * Copyright (c) 2001-2004 Viliam Holub
 */


#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <stdint.h>

#include "mtypes.h"
#include "parser.h"

struct device_type_s;
typedef struct device_type_s device_type_s;

/*
 * This structure describes a device instance.
 *
 * type		A pointer to the device type description.
 * 
 * name		A device name given by the user. Must be unique.
 * data		A device specific pointer where internal data are stored.
 *
 * next		A pointer to the next instance. NULL at the end.
 */

struct device_s
{
	const device_type_s *type;
	char *name;
	void *data;

	struct device_s *next;
};
typedef struct device_s device_s;


/*
 * device_type_s
 *
 * This structure describes functions which device can use.
 *
 * name		String constant - device type name (i82xx etc.)
 * desc_brief	A brief decription of the device type.
 * desc_full	A full textual device type description.
 * init		Inicialization, called once. There shoud be basic tests -
 * 		conflict detection, allocation memory etc. Returns
 * 		error string while fail.
 * done		Disposes internal data
 * step		Called every machine cycle.
 * read		Called while memory read command is out of memory. Device
 * 		shuld test addr if it is relevat.
 * write	Called when write memory command is out of memory. Device
 * 		should test addr param.
 * cmds		An array of commands supportred by the device. Have a look
 * 		at the device_cmd_struct structure for more information.
 * 		The last command should be the LAST_CMS macro.
 *
 * NULL value means "not implemented".
 */

struct device_type_s
{
	const char *const name;
	const char *const desc_brief;
	const char *const desc_full;
	
	void		(*done) ( device_s *d);
	void		(*step) ( device_s *d);
	void		(*read) ( device_s *d, uint32_t addr, uint32_t *val);
	void		(*write)( device_s *d, uint32_t addr, uint32_t val);

	const cmd_s *const cmds;
};

/*
 * LAST_CMD is used in device sources to determine the last command. That's
 * only a null-command with all NULL parameters.
 */
#define LAST_CMD	{}


/*
 * Device list is an array of all device types within sources.
 */
extern const device_type_s *device_types[];

/*
 * This string array has the most frequently messages for user.
 * Device implementation should preferable these.
 */

extern const char *txt_pub[];

/*
 * For info and stat output, please use info_printf at all times.
 * First parameter is a format string and other parameters are
 * optionally arguments as for printf().
 * INFO_SPC is a string constant useful for multi-line infos.
 */
void info_printf( const char *fmt, ...);
#define INFO_SPC "                      "

device_s *dev_by_name( const char *s);
const char *dev_by_partial_typename( const char *name,
		const device_type_s ***dt);
const char *dev_by_partial_name( const char *name, device_s **d);
int devs_by_partial_name( const char *name, device_s **d);
device_s *dev_by_name( const char *s);
bool dev_map( void *data, bool (*f)(void *, device_s *));
bool dev_next( device_s **d);
void cpr_num( char *s, uint32_t i);

void dev_add( device_s *d);
void dev_remove( device_s *d);

bool dev_generic_help( parm_link_s *parm, device_s *dev);
void find_dev_gen( parm_link_s **pl, const device_s *d,
		gen_f *generator, const void **data);


#endif /* _DEVICE_H_ */
