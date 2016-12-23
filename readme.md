Please use hhvm version latest 3.15 and necessary commands like "hphize"  <br />
Currently tested on ubuntu 64 bit machine  <br />

For compiling :  <br />
hphpize  <br />
cmake -DCMAKE_CXX_FLAGS='-fpermissive' . <br />
make  <br />

For installing:  <br />
cp vaeql.so /etc/hhvm/  <br />


Sample /etc/hhvm/php.ini  file (in repo) that should have some additional entries apart from the default ones:





