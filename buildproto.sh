cd protos

protoc -I=. --cpp_out=. ./mc/comm/*.proto

cd ..

mv protos/mc/comm/*.h others/include/mc/comm/

mv protos/mc/comm/*.cc src/mc/comm/

cd protos

protoc -I=. --go_out=. ./mc/comm/*.proto

cd ..

mv protos/mc/comm/*.pb.go cli/mc/comm/