# make sure disk is empty
# sudo fdisk -l							# list disks
sudo db if=./boot.bin of=./dev/sdb		# of -- output file && if -- input file
