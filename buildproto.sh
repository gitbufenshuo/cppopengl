cd protos

protoc -I=. --cpp_out=. ./mc/comm/*.proto

cd ..

mv protos/mc/comm/*.h others/include/mc/comm/

mv protos/mc/comm/*.cc src/mc/comm/
