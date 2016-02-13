#!/bin/sh

##Compile_src=$1
#echo="echo hello world"
#cd_assn="cd assn"
#ls_a="ls -a"
#wrong_echo="eco hi"
#exit_cmd="exit"

cd ../src/
make all

echo
echo
echo "****** FOR TESTING, ALL TEST CASES INCLUDE exit AS THE NEXT COMMAND LINE ******"
echo
echo

echo "****** testing: ls"
echo
./rshell.out <<'EOF'
ls
exit
EOF

echo
echo
echo "****** testing: echo hello world"
./rshell.out <<'EOF'
echo hello world
exit
EOF

echo
echo
echo "****** testing: cd assn"
./rshell.out <<'EOF'
cd assn
exit
EOF

echo
echo
echo "****** testing: ls -lh"
./rshell.out <<'EOF'
ls -lh
exit
EOF


echo
echo
echo "****** testing: exit"
./rshell.out <<'EOF'
exit
EOF


echo
echo
echo "****** testing: pwd"
./rshell.out <<'EOF'
pwd
exit
EOF

echo
echo
echo "****** testing: improper command eco hello world"
./rshell.out <<'EOF'
ecpeaso hello world
exit
EOF

