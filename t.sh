SERVER="localhost"  
PORT=4242    
CHANNEL="#RedRoom"
CLIENT_COUNT=300
PASS="root"

for ((i=1; i<=CLIENT_COUNT; i++))
do
    (
    NICKNAME="U${i}"
    echo "PASS $PASS"
    sleep 0.7
    echo "NICK $NICKNAME"
    sleep 0.7
    echo "USER ${i} 0 * ab"
    sleep 0.7
    echo "JOIN $CHANNEL"
	#sleep 0.7
	#echo "PART $CHANNEL"
	sleep 0.7
    echo "QUIT"
    sleep 40
    ) | nc $SERVER $PORT &
done
wait 
echo "Disconnected all clients from the server."
