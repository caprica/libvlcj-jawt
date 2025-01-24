#!/bin/bash
docker build --network host -o type=local,dest=./build -t libvlcj-awt-build .
