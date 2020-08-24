AC_INIT(ObjSQLite, 0.1, js@nil.im)
AC_CONFIG_SRCDIR(src)
AC_CONFIG_AUX_DIR(build-aux)
AC_CONFIG_MACRO_DIR(build-aux/m4)

for i in configure.ac build-aux/m4/*; do
	AS_IF([test $i -nt configure], [
		AC_MSG_ERROR([$i is newer than configure! Run ./autogen.sh!])
	])
done

BUILDSYS_INIT

AC_CHECK_TOOL(OBJFW_CONFIG, objfw-config)
AS_IF([test x"$OBJFW_CONFIG" = x""], [
	AC_MSG_ERROR(You need ObjFW and objfw-config installed!)
])

test x"$OBJC" = x"" && OBJC="$($OBJFW_CONFIG --objc)"

AC_LANG([Objective C])
AC_PROG_OBJC
AC_PROG_OBJCPP
AC_PROG_LN_S
AC_PROG_INSTALL

CPP="$OBJCPP"
CPPFLAGS="$CPPFLAGS $OBJCPPFLAGS $($OBJFW_CONFIG --cppflags)"
OBJCFLAGS="$OBJCFLAGS $($OBJFW_CONFIG --objcflags)"
LDFLAGS="$LDFLAGS $($OBJFW_CONFIG --ldflags)"
AC_SUBST(OBJFW_LIBS, "$($OBJFW_CONFIG --libs)")
AC_SUBST(OBJFW_FRAMEWORK_LIBS, "$($OBJFW_CONFIG --framework-libs)")

AX_CHECK_COMPILER_FLAGS(-Wdocumentation,
	[OBJCFLAGS="$OBJCFLAGS -Wdocumentation"])

AC_CHECK_TOOL(AR, ar)
AC_PROG_RANLIB
AC_ARG_ENABLE(shared,
	AS_HELP_STRING([--disable-shared], [do not build shared library]))
AS_IF([test x"$enable_shared" != x"no"], [
	BUILDSYS_SHARED_LIB
	AC_SUBST(OBJSQLITE_SHARED_LIB, "${LIB_PREFIX}objsqlite${LIB_SUFFIX}")
	AC_SUBST(EXCEPTIONS_LIB_A, "exceptions.lib.a")
	AC_SUBST(EXCEPTIONS_EXCEPTIONS_LIB_A, "exceptions/exceptions.lib.a")

	BUILDSYS_FRAMEWORK([
		AC_SUBST(OBJSQLITE_FRAMEWORK, "ObjSQLite.framework")
	])
])
AC_ARG_ENABLE(static, AS_HELP_STRING([--enable-static], [build static library]))
AS_IF([test x"$enable_static" = x"yes" -o x"$enable_shared" = x"no"], [
	AC_SUBST(OBJSQLITE_STATIC_LIB, "libobjsqlite.a")
	AC_SUBST(EXCEPTIONS_A, "exceptions.a")
	AC_SUBST(EXCEPTIONS_EXCEPTIONS_A, "exceptions/exceptions.a")
])

AC_ARG_WITH(sqlite, AS_HELP_STRING([--with-sqlite=PREFIX],
	[build with SQLite in the specified prefix]))
AS_IF([test x"$with_sqlite" != x"no" -a x"$with_sqlite" != x""], [
	SQLITE_CPPFLAGS="-I$with_sqlite/include"
	SQLITE_LIBS="-L$with_sqlite/lib"
	CPPFLAGS="$CPPFLAGS $SQLITE_CPPFLAGS"
	LIBS="$LIBS $SQLITE_LIBS"
])

AC_CHECK_LIB(sqlite3, main, [
	SQLITE_LIBS="$SQLITE_LIBS -lsqlite3"
	LIBS="$LIBS -lsqlite3"
], [
	AC_MSG_ERROR(You need SQLite3 and installed!)
])

AS_IF([test x"$GOBJC" = x"yes"], [
	OBJCFLAGS="$OBJCFLAGS -Wall -Werror -Wwrite-strings -Wpointer-arith"

	old_OBJCFLAGS="$OBJCFLAGS"
	OBJCFLAGS="$OBJCFLAGS -Wcast-align"
	AC_MSG_CHECKING(whether -Wcast-align is buggy)
	AC_TRY_COMPILE([
		#ifdef __has_attribute
		# if __has_attribute(objc_root_class)
		__attribute__((__objc_root_class__))
		# endif
		#endif
		@interface Foo
		{
			struct objc_class *_isa;
		}
		@end

		@implementation Foo
		- (void)foo
		{
			struct objc_class *c = _isa;
			(void)c;
		}
		@end
	], [
	], [
		AC_MSG_RESULT(no)
	], [
		AC_MSG_RESULT(yes)
		OBJCFLAGS="$old_OBJCFLAGS"
	])
])

dnl We don't call AC_PROG_CPP, but only AC_PROG_OBJCPP and set CPP to OBJCPP
dnl and add OBJCPPFLAGS to CPPFLAGS, thus we need to AC_SUBST these ourself.
AC_SUBST(CPP)
AC_SUBST(CPPFLAGS)

AC_SUBST(SQLITE_CFLAGS)
AC_SUBST(SQLITE_LIBS)

AC_CONFIG_FILES([buildsys.mk extra.mk ObjSQLite.oc])
AC_OUTPUT
