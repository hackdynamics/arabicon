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

#ifndef HEXCHAT_COMMONPLUGIN_H
#define HEXCHAT_COMMONPLUGIN_H

#ifdef PLUGIN_C
struct _arabicon_plugin
{
	/* Keep these in sync with arabicon-plugin.h */
	/* !!don't change the order, to keep binary compat!! */
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
	      const char *format, ...);
	void (*arabicon_command) (arabicon_plugin *ph,
	       const char *command);
	void (*arabicon_commandf) (arabicon_plugin *ph,
		const char *format, ...);
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
	void *(*arabicon_read_fd) (arabicon_plugin *ph);
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

	/* PRIVATE FIELDS! */
	void *handle;		/* from dlopen */
	char *filename;	/* loaded from */
	char *name;
	char *desc;
	char *version;
	session *context;
	void *deinit_callback;	/* pointer to arabicon_plugin_deinit */
	unsigned int fake:1;		/* fake plugin. Added by arabicon_plugingui_add() */
	unsigned int free_strings:1;		/* free name,desc,version? */
};
#endif

GModule *module_load (char *filename);
char *plugin_load (session *sess, char *filename, char *arg);
int plugin_reload (session *sess, char *name, int by_filename);
void plugin_add (session *sess, char *filename, void *handle, void *init_func, void *deinit_func, char *arg, int fake);
int plugin_kill (char *name, int by_filename);
void plugin_kill_all (void);
void plugin_auto_load (session *sess);
int plugin_emit_command (session *sess, char *name, char *word[], char *word_eol[]);
int plugin_emit_server (session *sess, char *name, char *word[], char *word_eol[],
						time_t server_time);
int plugin_emit_print (session *sess, char *word[], time_t server_time);
int plugin_emit_dummy_print (session *sess, char *name);
int plugin_emit_keypress (session *sess, unsigned int state, unsigned int keyval, gunichar key);
GList* plugin_command_list(GList *tmp_list);
int plugin_show_help (session *sess, char *cmd);
void plugin_command_foreach (session *sess, void *userdata, void (*cb) (session *sess, void *userdata, char *name, char *usage));
session *plugin_find_context (const char *servname, const char *channel, server *current_server);

/* On macOS, G_MODULE_SUFFIX says "so" but meson uses "dylib"
 * https://github.com/mesonbuild/meson/issues/1160 */
#if defined(__APPLE__)
#  define PLUGIN_SUFFIX "dylib"
#else
#  define PLUGIN_SUFFIX G_MODULE_SUFFIX
#endif

#endif
