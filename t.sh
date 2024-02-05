SERVER="localhost"  
PORT=4242    
CHANNEL="#RedRoom"
CLIENT_COUNT=100
PASS="root"

for ((i=1; i<=CLIENT_COUNT; i++))
do
    (
    NICKNAME="U${i}"
    echo "PASS $PASS"
    echo "NICK $NICKNAME"
    echo "USER ${i} 0 * ab"
    echo "JOIN $CHANNEL"
	sleep 0.1
    echo "PRIVMSG bot :hello"
    echo "QUIT"
	sleep 0
    ) | nc $SERVER $PORT &
done
wait 
echo "Disconnected all clients from the server."
