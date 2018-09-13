#! /bin/sh

session="app"
PORT="3000"

tmux start-server

tmux new-session -d -s $session

tmux splitw -h -t 0 -p 30
tmux splitw -v -t 1 -p 75
tmux send-keys -t 1 "python3.6 src/server.py $PORT" C-m
tmux send-keys -t 2 "python3.6 src/worker.py" C-m
tmux selectp -t 0


tmux a -t app
