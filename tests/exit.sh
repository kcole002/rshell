#!/bin/sh


cd ../src/
make all



echo
echo
echo "****** FOR TESTING, ALL TEST CASES INCLUDE exit AS THE NEXT COMMAND LINE ******"
echo
echo

echo "****** testing: exit ls -a; # echo hi || echo should not output && echo should output"
echo
./rshell.out <<'EOF'
exit ls -a; # echo hi || echo should not output && echo should output
EOF

echo
echo
echo "****** testing command: echo exit after this; exit && mkdir test"
echo
./rshell.out <<'EOF'
echo exit after this; exit && mkdir test
EOF

echo
echo
echo "****** testing: echo ouput this; echo and this || exit; echo output this as well && echo this too"
echo
./rshell.out <<'EOF'
echo ouput this; echo and this || exit; echo output this as well && echo this too
EOF

echo
echo
echo "****** testing command: echo this; echo will && echo exit now && exit"
echo
./rshell.out <<'EOF'
echo this; echo will && echo exit now && exit
EOF



