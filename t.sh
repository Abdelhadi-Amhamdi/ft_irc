SERVER="localhost"  
PORT=4242     
CHANNEL="#RedRoom"
CLIENT_COUNT=200
PASS="root"

for ((i=1; i<=CLIENT_COUNT; i++))
do
    (
    NICKNAME="U${i}"
    echo "PASS $PASS"
    sleep 0.5
    echo "NICK $NICKNAME"
    sleep 0.5
    echo "USER ${i} 0 * ab"
    sleep 0.5
    echo "JOIN $CHANNEL"
	sleep 0.5
	echo "PART $CHANNEL"
	sleep 0.5
    echo "QUIT"
    sleep 40
    ) | nc $SERVER $PORT &
done
wait 
echo "Disconnected all clients from the server."
