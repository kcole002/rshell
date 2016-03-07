#!/bin/sh


cd ../src/
make all

echo
echo
echo "****** FOR TESTING, ALL TEST CASES INCLUDE exit AS THE NEXT COMMAND LINE ******"
echo
echo

echo "***** precedence test 1: (echo A && echo B) || (echo C && echo D; echo E || echo F) && (echo G; echo I)"
echo
./rshell.out <<'EOF'
(echo A && echo B) || (echo C && echo D; echo E || echo F) && (echo G; echo I)
exit
EOF


echo "***** precedence test 2: echo A && echo B || (echo C && echo D; echo E || echo F)"
echo
./rshell.out <<'EOF'
echo A && echo B || (echo C && echo D; echo E || echo F)
exit
EOF


echo "***** precedence test 3: echo A && (echo B)"
echo
./rshell.out <<'EOF'
echo A && (echo B)
exit
EOF


echo "***** precedence test 4: echo C && echo D || (echo E || echo F)"
echo
./rshell.out <<'EOF'
echo C && echo D || (echo E || echo F)
exit
EOF


echo "***** precedence test 4: echo C && echo D && (echo E || echo F)"
echo
./rshell.out <<'EOF'
echo C && echo D && (echo E || echo F)
exit
EOF

