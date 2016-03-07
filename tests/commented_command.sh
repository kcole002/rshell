#!/bin/sh


cd ../src/
make all

echo
echo
echo "****** FOR TESTING, ALL TEST CASES INCLUDE exit AS THE NEXT COMMAND LINE ******"
echo
echo

echo "****** testing: ls -a; # echo hi || echo should not output && echo should output"
echo
./rshell.out <<'EOF'
ls -a; # echo hi || echo should not output && echo should output
exit
EOF

echo
echo
echo "****** testing: # echo A || echo should not print; mkdir test"
echo
./rshell.out <<'EOF'
# echo A || echo should not print; mkdir test
exit
EOF

echo
echo
echo "****** testing: echo ouput this; echo and this || # echo not this; echo output this as well && echo this too"
echo
./rshell.out <<'EOF'
echo ouput this; echo and this || # echo not this; echo output this as well && echo this too
exit
EOF

echo
echo
echo "****** testing: echo A && echo this; echo wont && # echo even output"
echo
./rshell.out <<'EOF'
echo A && echo this; echo wont && # echo even output
exit
EOF


echo
echo
echo "****** testing command line: ls || echo OR && echo after #exit && echo now exit; # exit"
echo
./rshell.out <<'EOF'
ls || echo OR && echo after #exit && echo now exit; # exit
exit
EOF


echo
echo
echo "****** testing command line: ls || echo OR && # test /home/csmajs/cdele005/CS100/Lab6/composite.cpp && echo now exit; exit"
echo
./rshell.out <<'EOF'
ls && echo OR && # test /home/csmajs/cdele005/CS100/Lab6/composite.cpp && echo now exit; exit
exit
EOF


echo
echo
echo "****** testing command line: ls &&  echo OR && [ /home/csmajs/cdele005/CS100/Lab6/composite.cpp ]"
echo
./rshell.out <<'EOF'
ls && echo OR && [ /home/csmajs/cdele005/CS100/Lab6/composite.cpp ]
exit
EOF
