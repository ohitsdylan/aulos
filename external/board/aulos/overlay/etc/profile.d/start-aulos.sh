tmux -f /etc/tmux.conf \
    new-session \; \
    split-window -h -p 33 \; \
    split-window -v \; \
    select-pane -t 0 \; \
    send-keys 'cmus' C-m \; \
    select-pane -t 1 \; \
    send-keys 'tock -c -m -C 7 -f ""' C-m \; \
    select-pane -t 2 \; \
    send-keys 'vis' C-m \; \
    select-pane -t 0 \;
