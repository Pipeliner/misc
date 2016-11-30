#!/bin/sh
echo 0|sudo tee /proc/sys/kernel/yama/ptrace_scope
./test &
sleep 3
./test2 &
sleep 3
gdb -p `pgrep test` -ex 'b foo.c:7' &
sleep 3
