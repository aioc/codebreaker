#!/bin/sh

session="app"
PORT="3000"

./setup.sh

tmux start-server

if tmux has -t=$session 2> /dev/null ; then
    tmux kill-session -t=$session
fi

tmux new-session -d -s $session

tmux splitw -h -t 0 -p 30
tmux splitw -v -t 1 -p 75
tmux send-keys -t 1 "python3 src/server.py $PORT" C-m
tmux send-keys -t 2 "python3 src/worker.py" C-m
tmux selectp -t 0

tmux a -t app
