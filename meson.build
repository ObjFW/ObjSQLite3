project('ObjSQLite3', 'objc',
  version: '0.1',
  meson_version: '>= 1.5.0',
  default_options: {
    'warning_level': '3',
  })

objfw_dep = dependency('objfw')
sqlite3_dep = dependency('sqlite3')

incdir = include_directories(['src', 'src/exceptions'])

# Meson unfortunately does not allow access to the flags of sqlite3_dep.
pkgconfig = find_program('pkg-config')
sqlite3_cflags = run_command([pkgconfig, '--cflags', 'sqlite3'], check: true)
sqlite3_libs = run_command([pkgconfig, '--libs', 'sqlite3'], check: true)

configure_file(
  input: 'ObjSQLite3.oc.in',
  output: 'ObjSQLite3.oc',
  configuration: {
    'libdir': get_option('prefix') / get_option('libdir'),
    'SQLITE3_CPPFLAGS': sqlite3_cflags.stdout().strip(),
    'SQLITE3_LIBS': sqlite3_libs.stdout().strip(),
  },
  install: true,
  install_dir: get_option('libdir') / 'objfw-config')

subdir('src')
subdir('tests')
