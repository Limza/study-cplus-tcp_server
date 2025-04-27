protoc.exe -I=./ --cpp_out=./ ./*.proto
IF ERRORLEVEL 1 PAUSE