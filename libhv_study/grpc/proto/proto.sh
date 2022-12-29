#!/bin/bash

cd `dirname $0`

PROTOC=`which protoc`
if [ $? -ne 0 ]; then
    echo "Not found command protoc!"
    echo "Please install libprotobuf first!"
    exit 1
fi

CPP_OUT_DIR=../generated
if [ ! -d "${CPP_OUT_DIR}" ]; then
    mkdir -p ${CPP_OUT_DIR}
fi

set -x
${PROTOC} --grpc_out=${CPP_OUT_DIR} --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` *.proto
${PROTOC} --cpp_out=${CPP_OUT_DIR} *.proto