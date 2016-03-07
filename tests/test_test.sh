#!/bin/sh


cd ../src/
make all

echo
echo
echo "****** FOR TESTING, ALL TEST CASES INCLUDE exit AS THE NEXT COMMAND LINE ******"
echo
echo

echo "***** directory test : test -d /home/csmajs/cdele005/CS100/"
echo
./rshell.out <<'EOF'
test -d /home/csmajs/cdele005/CS100/
exit
EOF

echo
echo
echo "****** regular file test : test -f /home/csmajs/cdele005/CS100/Lab6/composite.cpp"
./rshell.out <<'EOF'
test -e /home/csmajs/cdele005/CS100/Lab6/composite.cpp
exit
EOF

echo
echo
echo "****** bracket test : [/home/csmajs/cdele005/CS100/Lab6/composite.cpp] "
./rshell.out <<'EOF'
[/home/csmajs/cdele005/CS100/Lab6/composite.cpp]
exit
EOF

echo
echo
echo "****** test with connectors : test /home/csmajs/cdele005/CS100/Lab6/composite.cpp && echo path exists"
./rshell.out <<'EOF'
test /home/csmajs/cdele005/CS100/Lab6/composite.cpp && echo path exists
exit
EOF


echo
echo
echo "****** bracket with connectors test: [/home/csmajs/cdele005/CS100/Lab6/composite.cp] && echo path exists"
./rshell.out <<'EOF'
cd asdfg && echo AND && echo after exit && echo now exit; exit
[/home/csmajs/cdele005/CS100/Lab6/composite.cp] && echo path exists
exit
EOF


