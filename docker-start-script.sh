# start xvfb
/opt/bin/start-xvfb.sh &

# start vnc server
/opt/bin/start-vnc.sh &

echo "You can now connect your VNC client to http://localhost:5900 to view the application GUI\n"
