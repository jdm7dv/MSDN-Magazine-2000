del /F /Q *.ncb *.plg *.opt 

cd include
call makeclean.cmd
cd ..

cd stationery
call makeclean.cmd
cd ..

cd methodtimehook
call makeclean.cmd
cd ..

cd loadbalancingalgorithms
call makeclean.cmd
cd ..

cd loadbalancer
call makeclean.cmd
cd ..

cd testserver
call makeclean.cmd
cd ..

cd testclient
call makeclean.cmd
cd ..