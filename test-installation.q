#!/home/rob/q/l64/q

\l png.q

expectedDim:([] width:172 840 530 640i;height:151 884 298 156i)
actualDim:.png.dimensions each {` sv/: x,/:key x} `:images
expectedPx:0 0 255 255f
actualPx:{avg raze x} each value .png.pixels `:images/blueblock.png

verify:{[title;expected;actual]
  if[not expected~actual;
    -1 "=== ",title," ===";
    -1 "Expected:";
    show expected;
    -1 "Actual:";
    show actual;
    -1 (8+count[title])#"="];}

verify[".png.dimensions";expectedPx;actualPx]
verify[".png.pixels";expectedDim;actualDim]

-1 "Done";

exit 0
