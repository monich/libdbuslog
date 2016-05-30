/*
 * Copyright (C) 2016 Jolla Ltd.
 * Contact: Slava Monich <slava.monich@jolla.com>
 *
 * You may use this file under the terms of BSD license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *   3. Neither the name of Jolla Ltd nor the names of its contributors may
 *      be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DBUSLOG_SERVER_PRIVATE_H
#define DBUSLOG_SERVER_PRIVATE_H

#include "dbuslog_server.h"
#include "dbuslog_core.h"

#include <gutil_strv.h>

#define DBUSLOG_INTERFACE_VERSION (1)
#define DBUSLOG_LOG_COOKIE (1)

typedef struct dbus_log_server_priv DBusLogServerPriv;

struct dbus_log_server {
    GObject object;
    DBusLogServerPriv* priv;
    DBusLogCore* core;
    const char* path;
    gboolean started;
    gboolean exported;
};

typedef struct dbus_log_server_class {
    GObjectClass object;
    /* Peer watch */
    gulong
    (*watch_name)(
        DBusLogServer* self,
        const char* name);
    void
    (*unwatch_name)(
        DBusLogServer* self,
        gulong id);
    /* Export */
    gboolean
    (*export)(
        DBusLogServer* self);
    void
    (*unexport)(
        DBusLogServer* self);
    /* D-Bus signals */
    void
    (*emit_default_level_changed)(
        DBusLogServer* self);
    void
    (*emit_category_level_changed)(
        DBusLogServer* self,
        guint id,
        DBUSLOG_LEVEL level);
    void
    (*emit_category_added)(
        DBusLogServer* self,
        const char* name,
        guint id,
        guint flags);
    void
    (*emit_category_removed)(
        DBusLogServer* self,
        guint id);
    void
    (*emit_category_flags_changed)(
        DBusLogServer* self,
        guint id,
        guint flags);
} DBusLogServerClass;

GType dbus_log_server_get_type(void);
#define DBUSLOG_SERVER_TYPE (dbus_log_server_get_type())
#define DBUSLOG_SERVER(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), \
        DBUSLOG_SERVER_TYPE, DBusLogServer))

void
dbus_log_server_initialize(
    DBusLogServer* self,
    const char* path);

void
dbus_log_server_peer_vanished(
    DBusLogServer* self,
    const char* name);

int
dbus_log_server_open(
    DBusLogServer* server,
    const char* peer);

void
dbus_log_server_close(
    DBusLogServer* server,
    const char* peer,
    guint cookie);

void
dbus_log_server_set_names_enabled(
    DBusLogServer* server,
    const GStrV* names,
    gboolean enable);

void
dbus_log_server_set_pattern_enabled(
    DBusLogServer* self,
    const char* pattern,
    gboolean enable);

#endif /* DBUSLOG_SERVER_PRIVATE_H */

/*
 * Local Variables:
 * mode: C
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
