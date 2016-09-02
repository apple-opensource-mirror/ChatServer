#!@GAWK@ -f
# Example for use of GNU gettext.
# Copyright (C) 2003 Free Software Foundation, Inc.
# This file is in the public domain.
#
# Source code of the GNU awk program.

BEGIN {
  TEXTDOMAIN = "hello-gawk"
  bindtextdomain ("@localedir@")

  print _"Hello, world!"
  printf _"This program is running as process number %d.", PROCINFO["pid"]
  print
}
