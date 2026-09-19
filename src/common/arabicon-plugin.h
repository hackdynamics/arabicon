/* ARABICON
 * Copyright (C) 1998-2010 Peter Zelezny.
 * Copyright (C) 2009-2013 Berke Viktor.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* You can distribute this header with your plugins for easy compilation */
#ifndef HEXCHAT_PLUGIN_H
#define HEXCHAT_PLUGIN_H

#include <time.h>

#define HEXCHAT_PRI_HIGHEST	127
#define HEXCHAT_PRI_HIGH		64
#define HEXCHAT_PRI_NORM		0
#define HEXCHAT_PRI_LOW		(-64)
#define HEXCHAT_PRI_LOWEST	(-128)

#define HEXCHAT_FD_READ		1
#define HEXCHAT_FD_WRITE		2
#define HEXCHAT_FD_EXCEPTION	4
#define HEXCHAT_FD_NOTSOCKET	8

#define HEXCHAT_EAT_NONE		0	/* pass it on through! */
#define HEXCHAT_EAT_HEXCHAT		1	/* don't let ARABICON see this event */
#define HEXCHAT_EAT_PLUGIN	2	/* don't let other plugins see this event */
#define HEXCHAT_EAT_ALL		(HEXCHAT_EAT_HEXCHAT|HEXCHAT_EAT_PLUGIN)	/* don't let anything see this event */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _arabicon_plugin arabicon_plugin;
typedef struct _arabicon_list arabicon_list;
typedef struct _arabicon_hook arabicon_hook;
#ifndef PLUGIN_C
typedef struct _arabicon_context arabicon_context;
#endif
typedef struct
{
	time_t server_time_utc; /* 0 if not used */
} arabicon_event_attrs;

#ifndef PLUGIN_C
struct _arabicon_plugin
{
	/* these are only used on win32 */
	arabicon_hook *(*arabicon_hook_command) (arabicon_plugin *ph,
		    const char *name,
		    int pri,
		    int (*callback) (char *word[], char *word_eol[], void *user_data),
		    const char *help_text,
		    void *userdata);
	arabicon_hook *(*arabicon_hook_server) (arabicon_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[], void *user_data),
		   void *userdata);
	arabicon_hook *(*arabicon_hook_print) (arabicon_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], void *user_data),
		  void *userdata);
	arabicon_hook *(*arabicon_hook_timer) (arabicon_plugin *ph,
		  int timeout,
		  int (*callback) (void *user_data),
		  void *userdata);
	arabicon_hook *(*arabicon_hook_fd) (arabicon_plugin *ph,
		   int fd,
		   int flags,
		   int (*callback) (int fd, int flags, void *user_data),
		   void *userdata);
	void *(*arabicon_unhook) (arabicon_plugin *ph,
	      arabicon_hook *hook);
	void (*arabicon_print) (arabicon_plugin *ph,
	     const char *text);
	void (*arabicon_printf) (arabicon_plugin *ph,
	      const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
	;
	void (*arabicon_command) (arabicon_plugin *ph,
	       const char *command);
	void (*arabicon_commandf) (arabicon_plugin *ph,
		const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
	;
	int (*arabicon_nickcmp) (arabicon_plugin *ph,
	       const char *s1,
	       const char *s2);
	int (*arabicon_set_context) (arabicon_plugin *ph,
		   arabicon_context *ctx);
	arabicon_context *(*arabicon_find_context) (arabicon_plugin *ph,
		    const char *servname,
		    const char *channel);
	arabicon_context *(*arabicon_get_context) (arabicon_plugin *ph);
	const char *(*arabicon_get_info) (arabicon_plugin *ph,
		const char *id);
	int (*arabicon_get_prefs) (arabicon_plugin *ph,
		 const char *name,
		 const char **string,
		 int *integer);
	arabicon_list * (*arabicon_list_get) (arabicon_plugin *ph,
		const char *name);
	void (*arabicon_list_free) (arabicon_plugin *ph,
		 arabicon_list *xlist);
	const char * const * (*arabicon_list_fields) (arabicon_plugin *ph,
		   const char *name);
	int (*arabicon_list_next) (arabicon_plugin *ph,
		 arabicon_list *xlist);
	const char * (*arabicon_list_str) (arabicon_plugin *ph,
		arabicon_list *xlist,
		const char *name);
	int (*arabicon_list_int) (arabicon_plugin *ph,
		arabicon_list *xlist,
		const char *name);
	void * (*arabicon_plugingui_add) (arabicon_plugin *ph,
		     const char *filename,
		     const char *name,
		     const char *desc,
		     const char *version,
		     char *reserved);
	void (*arabicon_plugingui_remove) (arabicon_plugin *ph,
			void *handle);
	int (*arabicon_emit_print) (arabicon_plugin *ph,
			const char *event_name, ...);
	int (*arabicon_read_fd) (arabicon_plugin *ph,
			void *src,
			char *buf,
			int *len);
	time_t (*arabicon_list_time) (arabicon_plugin *ph,
		arabicon_list *xlist,
		const char *name);
	char *(*arabicon_gettext) (arabicon_plugin *ph,
		const char *msgid);
	void (*arabicon_send_modes) (arabicon_plugin *ph,
		  const char **targets,
		  int ntargets,
		  int modes_per_line,
		  char sign,
		  char mode);
	char *(*arabicon_strip) (arabicon_plugin *ph,
	     const char *str,
	     int len,
	     int flags);
	void (*arabicon_free) (arabicon_plugin *ph,
	    void *ptr);
	int (*arabicon_pluginpref_set_str) (arabicon_plugin *ph,
		const char *var,
		const char *value);
	int (*arabicon_pluginpref_get_str) (arabicon_plugin *ph,
		const char *var,
		char *dest);
	int (*arabicon_pluginpref_set_int) (arabicon_plugin *ph,
		const char *var,
		int value);
	int (*arabicon_pluginpref_get_int) (arabicon_plugin *ph,
		const char *var);
	int (*arabicon_pluginpref_delete) (arabicon_plugin *ph,
		const char *var);
	int (*arabicon_pluginpref_list) (arabicon_plugin *ph,
		char *dest);
	arabicon_hook *(*arabicon_hook_server_attrs) (arabicon_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[],
							arabicon_event_attrs *attrs, void *user_data),
		   void *userdata);
	arabicon_hook *(*arabicon_hook_print_attrs) (arabicon_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], arabicon_event_attrs *attrs,
						   void *user_data),
		  void *userdata);
	int (*arabicon_emit_print_attrs) (arabicon_plugin *ph, arabicon_event_attrs *attrs,
									 const char *event_name, ...);
	arabicon_event_attrs *(*arabicon_event_attrs_create) (arabicon_plugin *ph);
	void (*arabicon_event_attrs_free) (arabicon_plugin *ph,
									  arabicon_event_attrs *attrs);
};
#endif


arabicon_hook *
arabicon_hook_command (arabicon_plugin *ph,
		    const char *name,
		    int pri,
		    int (*callback) (char *word[], char *word_eol[], void *user_data),
		    const char *help_text,
		    void *userdata);

arabicon_event_attrs *arabicon_event_attrs_create (arabicon_plugin *ph);

void arabicon_event_attrs_free (arabicon_plugin *ph, arabicon_event_attrs *attrs);

arabicon_hook *
arabicon_hook_server (arabicon_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[], void *user_data),
		   void *userdata);

arabicon_hook *
arabicon_hook_server_attrs (arabicon_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[],
							arabicon_event_attrs *attrs, void *user_data),
		   void *userdata);

arabicon_hook *
arabicon_hook_print (arabicon_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], void *user_data),
		  void *userdata);

arabicon_hook *
arabicon_hook_print_attrs (arabicon_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], arabicon_event_attrs *attrs,
						   void *user_data),
		  void *userdata);

arabicon_hook *
arabicon_hook_timer (arabicon_plugin *ph,
		  int timeout,
		  int (*callback) (void *user_data),
		  void *userdata);

arabicon_hook *
arabicon_hook_fd (arabicon_plugin *ph,
		int fd,
		int flags,
		int (*callback) (int fd, int flags, void *user_data),
		void *userdata);

void *
arabicon_unhook (arabicon_plugin *ph,
	      arabicon_hook *hook);

void
arabicon_print (arabicon_plugin *ph,
	     const char *text);

void
arabicon_printf (arabicon_plugin *ph,
	      const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
;

void
arabicon_command (arabicon_plugin *ph,
	       const char *command);

void
arabicon_commandf (arabicon_plugin *ph,
		const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
;

int
arabicon_nickcmp (arabicon_plugin *ph,
	       const char *s1,
	       const char *s2);

int
arabicon_set_context (arabicon_plugin *ph,
		   arabicon_context *ctx);

arabicon_context *
arabicon_find_context (arabicon_plugin *ph,
		    const char *servname,
		    const char *channel);

arabicon_context *
arabicon_get_context (arabicon_plugin *ph);

const char *
arabicon_get_info (arabicon_plugin *ph,
		const char *id);

int
arabicon_get_prefs (arabicon_plugin *ph,
		 const char *name,
		 const char **string,
		 int *integer);

arabicon_list *
arabicon_list_get (arabicon_plugin *ph,
		const char *name);

void
arabicon_list_free (arabicon_plugin *ph,
		 arabicon_list *xlist);

const char * const *
arabicon_list_fields (arabicon_plugin *ph,
		   const char *name);

int
arabicon_list_next (arabicon_plugin *ph,
		 arabicon_list *xlist);

const char *
arabicon_list_str (arabicon_plugin *ph,
		arabicon_list *xlist,
		const char *name);

int
arabicon_list_int (arabicon_plugin *ph,
		arabicon_list *xlist,
		const char *name);

time_t
arabicon_list_time (arabicon_plugin *ph,
		 arabicon_list *xlist,
		 const char *name);

void *
arabicon_plugingui_add (arabicon_plugin *ph,
		     const char *filename,
		     const char *name,
		     const char *desc,
		     const char *version,
		     char *reserved);

void
arabicon_plugingui_remove (arabicon_plugin *ph,
			void *handle);

int 
arabicon_emit_print (arabicon_plugin *ph,
		  const char *event_name, ...);

int 
arabicon_emit_print_attrs (arabicon_plugin *ph, arabicon_event_attrs *attrs,
						  const char *event_name, ...);

char *
arabicon_gettext (arabicon_plugin *ph,
	       const char *msgid);

void
arabicon_send_modes (arabicon_plugin *ph,
		  const char **targets,
		  int ntargets,
		  int modes_per_line,
		  char sign,
		  char mode);

char *
arabicon_strip (arabicon_plugin *ph,
	     const char *str,
	     int len,
	     int flags);

void
arabicon_free (arabicon_plugin *ph,
	    void *ptr);

int
arabicon_pluginpref_set_str (arabicon_plugin *ph,
		const char *var,
		const char *value);

int
arabicon_pluginpref_get_str (arabicon_plugin *ph,
		const char *var,
		char *dest);

int
arabicon_pluginpref_set_int (arabicon_plugin *ph,
		const char *var,
		int value);
int
arabicon_pluginpref_get_int (arabicon_plugin *ph,
		const char *var);

int
arabicon_pluginpref_delete (arabicon_plugin *ph,
		const char *var);

int
arabicon_pluginpref_list (arabicon_plugin *ph,
		char *dest);

#if !defined(PLUGIN_C) && (defined(WIN32) || defined(__CYGWIN__))
#ifndef HEXCHAT_PLUGIN_HANDLE
#define HEXCHAT_PLUGIN_HANDLE (ph)
#endif
#define arabicon_hook_command ((HEXCHAT_PLUGIN_HANDLE)->arabicon_hook_command)
#define arabicon_event_attrs_create ((HEXCHAT_PLUGIN_HANDLE)->arabicon_event_attrs_create)
#define arabicon_event_attrs_free ((HEXCHAT_PLUGIN_HANDLE)->arabicon_event_attrs_free)
#define arabicon_hook_server ((HEXCHAT_PLUGIN_HANDLE)->arabicon_hook_server)
#define arabicon_hook_server_attrs ((HEXCHAT_PLUGIN_HANDLE)->arabicon_hook_server_attrs)
#define arabicon_hook_print ((HEXCHAT_PLUGIN_HANDLE)->arabicon_hook_print)
#define arabicon_hook_print_attrs ((HEXCHAT_PLUGIN_HANDLE)->arabicon_hook_print_attrs)
#define arabicon_hook_timer ((HEXCHAT_PLUGIN_HANDLE)->arabicon_hook_timer)
#define arabicon_hook_fd ((HEXCHAT_PLUGIN_HANDLE)->arabicon_hook_fd)
#define arabicon_unhook ((HEXCHAT_PLUGIN_HANDLE)->arabicon_unhook)
#define arabicon_print ((HEXCHAT_PLUGIN_HANDLE)->arabicon_print)
#define arabicon_printf ((HEXCHAT_PLUGIN_HANDLE)->arabicon_printf)
#define arabicon_command ((HEXCHAT_PLUGIN_HANDLE)->arabicon_command)
#define arabicon_commandf ((HEXCHAT_PLUGIN_HANDLE)->arabicon_commandf)
#define arabicon_nickcmp ((HEXCHAT_PLUGIN_HANDLE)->arabicon_nickcmp)
#define arabicon_set_context ((HEXCHAT_PLUGIN_HANDLE)->arabicon_set_context)
#define arabicon_find_context ((HEXCHAT_PLUGIN_HANDLE)->arabicon_find_context)
#define arabicon_get_context ((HEXCHAT_PLUGIN_HANDLE)->arabicon_get_context)
#define arabicon_get_info ((HEXCHAT_PLUGIN_HANDLE)->arabicon_get_info)
#define arabicon_get_prefs ((HEXCHAT_PLUGIN_HANDLE)->arabicon_get_prefs)
#define arabicon_list_get ((HEXCHAT_PLUGIN_HANDLE)->arabicon_list_get)
#define arabicon_list_free ((HEXCHAT_PLUGIN_HANDLE)->arabicon_list_free)
#define arabicon_list_fields ((HEXCHAT_PLUGIN_HANDLE)->arabicon_list_fields)
#define arabicon_list_next ((HEXCHAT_PLUGIN_HANDLE)->arabicon_list_next)
#define arabicon_list_str ((HEXCHAT_PLUGIN_HANDLE)->arabicon_list_str)
#define arabicon_list_int ((HEXCHAT_PLUGIN_HANDLE)->arabicon_list_int)
#define arabicon_plugingui_add ((HEXCHAT_PLUGIN_HANDLE)->arabicon_plugingui_add)
#define arabicon_plugingui_remove ((HEXCHAT_PLUGIN_HANDLE)->arabicon_plugingui_remove)
#define arabicon_emit_print ((HEXCHAT_PLUGIN_HANDLE)->arabicon_emit_print)
#define arabicon_emit_print_attrs ((HEXCHAT_PLUGIN_HANDLE)->arabicon_emit_print_attrs)
#define arabicon_list_time ((HEXCHAT_PLUGIN_HANDLE)->arabicon_list_time)
#define arabicon_gettext ((HEXCHAT_PLUGIN_HANDLE)->arabicon_gettext)
#define arabicon_send_modes ((HEXCHAT_PLUGIN_HANDLE)->arabicon_send_modes)
#define arabicon_strip ((HEXCHAT_PLUGIN_HANDLE)->arabicon_strip)
#define arabicon_free ((HEXCHAT_PLUGIN_HANDLE)->arabicon_free)
#define arabicon_pluginpref_set_str ((HEXCHAT_PLUGIN_HANDLE)->arabicon_pluginpref_set_str)
#define arabicon_pluginpref_get_str ((HEXCHAT_PLUGIN_HANDLE)->arabicon_pluginpref_get_str)
#define arabicon_pluginpref_set_int ((HEXCHAT_PLUGIN_HANDLE)->arabicon_pluginpref_set_int)
#define arabicon_pluginpref_get_int ((HEXCHAT_PLUGIN_HANDLE)->arabicon_pluginpref_get_int)
#define arabicon_pluginpref_delete ((HEXCHAT_PLUGIN_HANDLE)->arabicon_pluginpref_delete)
#define arabicon_pluginpref_list ((HEXCHAT_PLUGIN_HANDLE)->arabicon_pluginpref_list)
#endif

#ifdef __cplusplus
}
#endif
#endif
