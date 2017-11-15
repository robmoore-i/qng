#!/home/rob/q/l64/q

\l png.q

expectedDim:([] width:172 840 530 640i;height:151 884 298 156i)
actualDim:.png.dimensions each {` sv/: x,/:key x} `:images
expectedPx:0 0 255 255f
actualPx:{avg raze x} each value .png.pixels `:images/blueblock.png
$[and[actualDim~expectedDim;actualPx~expectedPx];
  -1 "Passed";
  -1 "Failed. Try \"q png.q\" and verify the commands in this script"];

exit 0
