rm build/ocap_exporter.so

rm build/ocap_exporter_test

gcc -shared -Wall -Werror -fPIC -m32 -o build/ocap_exporter.so source/ocap_exporter.c

gcc -Lbuild/ -m32 -o build/ocap_exporter_test source/ocap_exporter_test.c -l:ocap_exporter.so

chmod 755 build/ocap_exporter_test

export LD_LIBRARY_PATH=build
