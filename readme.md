Please use hhvm version latest 3.15 and necessary commands like "hphize"
Currently tested on ubuntu 64 bit machine 

For compiling :
hphpize 
cmake -DCMAKE_CXX_FLAGS='-fpermissive'
make

For installing:
cp vaeql.so /etc/hhvm/


Sample /etc/hhvm/php.ini  file (in repo) that should have some additional entries apart from the default ones:





