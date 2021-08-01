set SRC_PATH=llvm10

echo downloading...

git clone --branch release/10.x -v "https://github.com/llvm/llvm-project.git"  %SRC_PATH%

echo patching...
#cp -R -v patch/* avro-src-1.10.2/
