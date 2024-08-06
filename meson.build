project('ObjSQLite3', 'objc',
  version: '0.1',
  meson_version: '>= 1.5.0',
  default_options: {
    'warning_level': '3',
  })

objfw_dep = dependency('objfw')
sqlite3_dep = dependency('sqlite3')

incdir = include_directories('src', 'src/exceptions')

subdir('src')
subdir('tests')

# Meson unfortunately does not allow access to the flags of sqlite3_dep.
pkgconfig = find_program('pkg-config')
sqlite3_cflags = run_command(
  [pkgconfig, '--cflags', 'sqlite3'],
  check: true).stdout().strip()
sqlite3_libs = run_command(
  [pkgconfig, '--libs', 'sqlite3'],
  check: true).stdout().strip()

objfwconfig = find_program('objfw-config')
packages_dir = run_command(
  [objfwconfig, '--packages-dir'],
  check: true).stdout().strip()

configure_file(
  input: 'ObjSQLite3.oc.in',
  output: 'ObjSQLite3.oc',
  configuration: {
    'libdir': get_option('prefix') / get_option('libdir'),
    'SQLITE3_CPPFLAGS': sqlite3_cflags,
    'SQLITE3_LIBS': sqlite3_libs,
  },
  install: true,
  install_dir: packages_dir)
