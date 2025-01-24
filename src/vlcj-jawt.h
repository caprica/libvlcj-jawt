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

#include <jni.h>

#ifndef _included_vlcj_jawt
#define _included_vlcj_jawt
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     uk_co_caprica_vlcj_jawt_VlcjJawt
 * Method:    getNativeWindowHandle
 * Signature: (Ljava/awt/Component;)J
 */
JNIEXPORT jlong JNICALL Java_uk_co_caprica_vlcj_jawt_VlcjJawt_getNativeWindowHandle
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
