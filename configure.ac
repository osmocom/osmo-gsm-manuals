dnl Process this file with autoconf to produce a configure script
AC_INIT([osmo-gsm-manuals],
	m4_esyscmd([./git-version-gen .tarball-version]),
	[openbsc@lists.osmocom.org])

dnl *This* is the root dir, even if an install-sh exists in ../ or ../../
AC_CONFIG_AUX_DIR([.])

AM_INIT_AUTOMAKE([foreign dist-bzip2 1.6 subdir-objects])

dnl include release helper
RELMAKE='-include osmo-release.mk'
AC_SUBST([RELMAKE])

dnl checks for programs
AC_PROG_INSTALL
LT_INIT

dnl check for pkg-config (explained in detail in libosmocore/configure.ac)
AC_PATH_PROG(PKG_CONFIG_INSTALLED, pkg-config, no)
if test "x$PKG_CONFIG_INSTALLED" = "xno"; then
        AC_MSG_WARN([You need to install pkg-config])
fi
PKG_PROG_PKG_CONFIG([0.20])

if ! $srcdir/check-depends.sh
then
	AC_MSG_ERROR("missing dependencies!")
fi

# Asciidoc warnings check (OS#4140)
AC_ARG_ENABLE(asciidoc_warnings_check,
	[AS_HELP_STRING(
		[--enable-asciidoc-warnings-check],
		[Fail the build if asciidoc prints any warnings]
	)],
	[asciidoc_warnings_check=$enableval], [asciidoc_warnings_check="no"])
AM_CONDITIONAL([ASCIIDOC_WARNINGS_CHECK], [test x"$asciidoc_warnings_check" = x"yes"])

AC_OUTPUT(
    osmo-gsm-manuals.pc
    Makefile
    tests/Makefile)
