trap 'echo catched usr1' SIGUSR1
trap 'echo catched usr2' SIGUSR2

while [ 1 ]; do
	sleep 1
done
