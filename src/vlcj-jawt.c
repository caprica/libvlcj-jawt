/*
 * This file is part of VLCJ-JAWT.
 *
 * VLCJ-JAWT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * VLCJ-JAWT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VLCJ-JAWT.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2025 Caprica Software Limited.
 */

#include <stdio.h>
#include <jawt.h>
#include <jni.h>
#include <jawt_md.h>

#include "vlcj-jawt.h"

#define INVALID_HANDLE -1L;

/**
 * @brief get the native window handle for an AWT component
 *
 * @param env JNI environment context
 * @param object Java object invoking the method
 * @param component method parameter
 * @return window handle if available, or -1
 * @throws RuntimeException if something failed, an extremely unlikely low-level error
 */
JNIEXPORT jlong JNICALL Java_uk_co_caprica_vlcj_jawt_VlcjJawt_getNativeWindowHandle(JNIEnv* env, jobject object, jobject component) {
    JAWT awt;
    JAWT_DrawingSurface *ds = NULL;
    JAWT_DrawingSurfaceInfo *dsi = NULL;

    jint lock = JAWT_LOCK_ERROR;
    jboolean getAWTResult;
    jlong handle = INVALID_HANDLE;

    const char* error = NULL;

    if (!component) {
        return INVALID_HANDLE;
    }

    awt.version = JAWT_VERSION_9;

    getAWTResult = JAWT_GetAWT(env, &awt);
    if (getAWTResult == JNI_FALSE) {
        error = "Unable to get AWT";
        goto cleanup;
    }

    ds = awt.GetDrawingSurface(env, component);
    if (ds == NULL) {
        error = "Unable to get drawing surface";
        goto cleanup;
    }

    lock = ds->Lock(ds);
    if ((lock & JAWT_LOCK_ERROR) != 0) {
        error = "Unable to lock drawing surface";
        goto cleanup;
    }

    dsi = ds->GetDrawingSurfaceInfo(ds);
    if (dsi == NULL) {
        error = "Unable to get drawing surface info";
        goto cleanup;
    }

    #ifdef __linux__
        JAWT_X11DrawingSurfaceInfo* x11dsi = (JAWT_X11DrawingSurfaceInfo*) dsi->platformInfo;
        if (x11dsi != NULL) {
            handle = x11dsi->drawable;
        }
    #endif

    #ifdef _WIN32
        JAWT_Win32DrawingSurfaceInfo* wdsi = (JAWT_Win32DrawingSurfaceInfo*) dsi->platformInfo;
        if (wdsi != NULL) {
            handle = (jlong) (wdsi->hwnd);
        }
    #endif

cleanup:
    if (dsi) {
        ds->FreeDrawingSurfaceInfo(dsi);
    }

    if ((lock & JAWT_LOCK_ERROR) == 0) {
        ds->Unlock(ds);
    }

    if (ds) {
        awt.FreeDrawingSurface(ds);
    }

    if (error) {
        jclass exceptionClass = (*env)->FindClass(env, "java/lang/RuntimeException");
        if (exceptionClass == NULL) {
            return INVALID_HANDLE;
        }
        (*env)->ThrowNew(env, exceptionClass, error);
        return INVALID_HANDLE;
    }

    return handle;
}
