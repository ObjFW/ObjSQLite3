objsqlite3 = library('objsqlite3',
  [
    'SL3Connection.m',
    'SL3PreparedStatement.m',
    'exceptions/SL3BindObjectFailedException.m',
    'exceptions/SL3ClearBindingsFailedException.m',
    'exceptions/SL3Exception.m',
    'exceptions/SL3ExecuteStatementFailedException.m',
    'exceptions/SL3OpenFailedException.m',
    'exceptions/SL3PrepareStatementFailedException.m',
    'exceptions/SL3ResetStatementFailedException.m',
  ],
  include_directories: incdir,
  objc_args: ['-DSL3_PUBLIC_IVARS'],
  dependencies: [objfw_dep, sqlite3_dep],
  install: true)

install_headers(
  [
    'ObjSQLite3.h',
    'SL3Connection.h',
    'SL3PreparedStatement.h',
    'exceptions/SL3BindObjectFailedException.h',
    'exceptions/SL3ClearBindingsFailedException.h',
    'exceptions/SL3Exception.h',
    'exceptions/SL3ExecuteStatementFailedException.h',
    'exceptions/SL3OpenFailedException.h',
    'exceptions/SL3PrepareStatementFailedException.h',
    'exceptions/SL3ResetStatementFailedException.h',
  ],
  subdir: 'ObjSQLite3')
