arabicon_gtk_sources = [
  'ascii.c',
  'banlist.c',
  'chanlist.c',
  'chanview.c',
  'custom-list.c',
  'dccgui.c',
  'editlist.c',
  'fe-gtk.c',
  'fkeys.c',
  'gtkutil.c',
  'ignoregui.c',
  'joind.c',
  'menu.c',
  'maingui.c',
  'notifygui.c',
  'palette.c',
  'pixmaps.c',
  'plugin-tray.c',
  'plugin-notification.c',
  'rawlog.c',
  'servlistgui.c',
  'setup.c',
  'sexy-spell-entry.c',
  'textgui.c',
  'urlgrab.c',
  'userlistgui.c',
  'xtext.c'
]

gtk_dep = dependency('gtk+-2.0', version: '>= 2.24.0')
arabicon_gtk_deps = [
  arabicon_common_dep,
  libgmodule_dep, # used by libsexy
  gtk_dep
]

if gtk_dep.get_pkgconfig_variable('target') == 'x11'
  arabicon_gtk_deps += dependency('x11')
endif

arabicon_gtk_cflags = []

arabicon_gtk_ldflags = []

if host_machine.system() == 'windows'
  arabicon_gtk_sources += 'notifications/notification-windows.c'

  # TODO: mingw doesn't have these headers or libs
  # add_languages('cpp')
  # shared_module('hcnotifications-winrt',
  #  sources: 'notifications/notification-winrt.cpp'
  #)

else
  arabicon_gtk_sources += 'notifications/notification-freedesktop.c'
endif

iso_codes = dependency('iso-codes', required: false)
if iso_codes.found()
  arabicon_gtk_sources += 'sexy-iso-codes.c'
  iso_codes_prefix = iso_codes.get_pkgconfig_variable('prefix')
  arabicon_gtk_cflags += '-DISO_CODES_PREFIX="@0@"'.format(iso_codes_prefix)
  arabicon_gtk_cflags += '-DISO_CODES_LOCALEDIR="@0@"'.format(
                        join_paths(iso_codes_prefix, 'share/locale'))
endif

if get_option('plugin')
  arabicon_gtk_sources += 'plugingui.c'
endif

resources = gnome.compile_resources('resources',
  '../../data/arabicon.gresource.xml',
  source_dir: '../../data', # TODO: Fix upstream
  c_name: 'arabicon',
  extra_args: ['--manual-register']
)

if host_machine.system() == 'windows'
  arabicon_gtk_ldflags += '-Wl,-e,mainCRTStartup'
endif

executable('arabicon',
  sources:  resources + arabicon_gtk_sources,
  dependencies: arabicon_gtk_deps,
  c_args: arabicon_gtk_cflags,
  link_args: arabicon_gtk_ldflags,
  pie: true,
  install: true,
  gui_app: true,
)
