/* 
 * Copyright (C) 2001, 2002 Red Hat Inc.
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef PKG_CONFIG_PKG_H
#define PKG_CONFIG_PKG_H

#ifdef USE_INSTALLED_GLIB
#include <glib.h>
#else
#include "partial-glib.h"
#endif

typedef enum
{
  LESS_THAN,
  GREATER_THAN,
  LESS_THAN_EQUAL,
  GREATER_THAN_EQUAL,
  EQUAL,
  NOT_EQUAL,
  ALWAYS_MATCH
} ComparisonType;

typedef struct _Package Package;
typedef struct _RequiredVersion RequiredVersion;

struct _RequiredVersion
{
  char *name;
  ComparisonType comparison;
  char *version;
  Package *owner;
};

struct _Package
{
  char *key;  /* filename name */
  char *name; /* human-readable name */
  char *version;
  char *description;
  char *pcfiledir; /* directory it was loaded from */
  GSList *requires;
  GSList *l_libs;
  char   *l_libs_merged;
  GSList *L_libs;
  char   *L_libs_merged;
  GSList *other_libs;
  char   *other_libs_merged;
  GSList *I_cflags;
  char   *I_cflags_merged;
  GSList *other_cflags;
  char *other_cflags_merged;
  GHashTable *vars;
  GHashTable *required_versions; /* hash from name to RequiredVersion */
  GSList *conflicts; /* list of RequiredVersion */
  gboolean uninstalled; /* used the -uninstalled file */
  int path_position; /* used to order packages by position in path of their .pc file, lower number means earlier in path */
};

Package *get_package              (const char *name);
char *   package_get_l_libs       (Package    *pkg);
char *   packages_get_l_libs      (GSList     *pkgs);
char *   package_get_L_libs       (Package    *pkg);
char *   packages_get_L_libs      (GSList     *pkgs);
char *   package_get_other_libs   (Package    *pkg);
char *   packages_get_other_libs  (GSList     *pkgs);
char *   packages_get_all_libs    (GSList     *pkgs);
char *   package_get_I_cflags     (Package    *pkg);
char *   packages_get_I_cflags    (GSList     *pkgs);
char *   package_get_other_cflags (Package    *pkg);
char *   packages_get_all_cflags  (GSList     *pkgs);
char *   package_get_var          (Package    *pkg,
                                   const char *var);
char *   packages_get_var          (GSList     *pkgs,
                                    const char *var);


void add_search_dir (const char *path);
void package_init (void);
int compare_versions (const char * a, const char *b);
gboolean version_test (ComparisonType comparison,
                       const char *a,
                       const char *b);

const char *comparison_to_str (ComparisonType comparison);

void print_package_list (void);

void define_global_variable (const char *varname,
                             const char *varval);

void debug_spew (const char *format, ...);
void verbose_error (const char *format, ...);

gboolean name_ends_in_uninstalled (const char *str);

/* If TRUE, do not automatically prefer uninstalled versions */
extern gboolean disable_uninstalled;

#ifdef G_OS_WIN32
/* If TRUE, do not automatically define "prefix"  while
 * parsing each .pc file */
extern int dont_define_prefix;
/* The name of the variable that acts as prefix, unless it is "prefix" */
extern char *prefix_variable;

/* If TRUE, output flags in MSVC syntax. */
extern int msvc_syntax;
#endif

#endif

