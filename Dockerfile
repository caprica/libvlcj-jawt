#
# This file is part of VLCJ-JAWT.
#
# VLCJ-JAWT is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# VLCJ-JAWT is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with VLCJ-JAWT.  If not, see <http://www.gnu.org/licenses/>.
#
# Copyright 2025 Caprica Software Limited.
#

FROM debian:bullseye as native-build

ENV DOCKER_BUILDKIT=1

ARG JAVA_VERSION=11
ARG JAVA_HOME=/usr/lib/jvm/java-${JAVA_VERSION}-openjdk-amd64

ARG WINDOWS_JAVA_VERSION=11.0.25+9
ARG WINDOWS_JAVA_HOME=/windows-jdk

ARG LIB_SRC=vlcj-jawt.c
ARG LIB_NAME=libvlcj-jawt

RUN apt-get update && \
    apt-get install -y \
        build-essential \
        gcc \
        mingw-w64 \
        openjdk-${JAVA_VERSION}-jdk \
        unzip \
        wget \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    && wget -nv https://builds.openlogic.com/downloadJDK/openlogic-openjdk/${WINDOWS_JAVA_VERSION}/openlogic-openjdk-${WINDOWS_JAVA_VERSION}-windows-x64.zip -O /tmp/openjdk-windows.zip \
    && unzip /tmp/openjdk-windows.zip "*/include/*" "*/lib/*" -d /tmp/ \
    && mkdir -p ${WINDOWS_JAVA_HOME}/include \
    && cp -r /tmp/openlogic-openjdk-${WINDOWS_JAVA_VERSION}-windows-x64/include ${WINDOWS_JAVA_HOME} \
    && cp -r /tmp/openlogic-openjdk-${WINDOWS_JAVA_VERSION}-windows-x64/lib ${WINDOWS_JAVA_HOME}

WORKDIR /src
COPY src/*.c .
COPY src/*.h .

RUN mkdir -p /build \
    && gcc                                   \
        -shared                              \
        -fPIC                                \
        -I${JAVA_HOME}/include               \
        -I${JAVA_HOME}/include/linux         \
        ${LIB_SRC}                           \
        -o /build/${LIB_NAME}.so             \
        -L${JAVA_HOME}/lib                   \
        -ljawt                               \
    && x86_64-w64-mingw32-gcc                \
        -shared                              \
        -I${WINDOWS_JAVA_HOME}/include       \
        -I${WINDOWS_JAVA_HOME}/include/win32 \
        ${LIB_SRC}                           \
        -o /build/${LIB_NAME}.dll            \
        -L${WINDOWS_JAVA_HOME}/lib           \
        -ljawt

FROM scratch

COPY --from=native-build build/*.so .
COPY --from=native-build build/*.dll .
