#!/bin/bash
if [[ $QHOME == "" ]]
then
  echo "Set QHOME first! Commands below:"
  echo "sudo su"
  echo "echo \"QHOME=/path/to/your/q/\" >> /etc/environment"
  echo "exit"
  echo "source /etc/environment"
  exit 1
fi

if [[ ! -d $QHOME ]]
then
  echo "QHOME directory not found: $QHOME"
  exit 0
fi

if [[ ! -f $QHOME/l64/q ]]
then
  echo "64 bit q executable not found: $QHOME/l64/q"
  exit 0
fi

echo "Environment variables seem okay"
echo "Checking dependencies"
./install-dependencies.sh
echo "Compiling C and sending to $QHOME/l64/"
./compile-shared-lib.sh libpngk.c
echo "Setting up installation verification script"
hashbang="#!$QHOME/l64/q"
sed -i "1c$hashbang" test-installation.q
echo "Verifying installation"
$QHOME/l64/q test-installation.q -q
echo "Copying png.q to QHOME"
cp png.q $QHOME
echo "All done"
exit 0
