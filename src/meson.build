fs = import('fs')

subdir('exceptions')

sources = files(
  'SL3Connection.m',
  'SL3PreparedStatement.m',
)

objsqlite3 = library('objsqlite3',
  sources + exceptions_sources,
  include_directories: incdir,
  objc_args: ['-DSL3_PUBLIC_IVARS'],
  dependencies: [objfw_dep, sqlite3_dep],
  soversion: '0.0',
  install: true)

headers = ['ObjSQLite3.h']
foreach source: sources + exceptions_sources
  headers += fs.replace_suffix(source.full_path(), '.h')
endforeach

install_headers(headers, subdir: 'ObjSQLite3')
