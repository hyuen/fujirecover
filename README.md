# fujirecover
utility to recover raw fuji files from a corrupted drive

make a copy of the corrupted drive into a local file, eg:

dd if=/dev/sdc1 of=corrupted.img bs=1M count=10000

look for the magic header "FUJIFILMCCD-RAW" and assume that all the files are contiguous
https://libopenraw.freedesktop.org/formats/raf/

extract a RAW file for each file encountered

g++ extract.cc -fpermissive
./a.out


![Alt text](./darktable.png?raw=true "Recovered files")

