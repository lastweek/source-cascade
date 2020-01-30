#!/bin/sh

# Constant Defintiions

export SDCARD=/dev/sdb

# Install apt dependencies

sudo apt-get update
sudo apt-get install bison flex libc6-i386 make wget

# Copy root file system

if [ ! -d rootfs ]; then
  mkdir rootfs
  sudo tar -xf download/ubuntu.tar.gz -C rootfs
  sudo cp data/fstab rootfs/etc/
fi

# Write Image

sudo dd if=/dev/zero of=sdcard.img bs=1 count=0 seek=512M
export LOOPBACK=`sudo losetup --show -f sdcard.img`

sudo sfdisk ${LOOPBACK} -uS << EOF
,32M,b
,470M,83
,10M,A2
EOF
sudo partprobe ${LOOPBACK}

sudo dd if=data/preloader-mkpimage.bin of=${LOOPBACK}p3 bs=64k seek=0

sudo mkfs -t vfat ${LOOPBACK}p1
mkdir fat_mount
sudo mount ${LOOPBACK}p1 fat_mount/
sudo cp data/u-boot.img data/u-boot.scr data/soc_system.dtb data/soc_system.rbf data/zImage fat_mount/
sync
sudo umount fat_mount
rmdir fat_mount

sudo mkfs.ext4 ${LOOPBACK}p2
mkdir ext_mount
sudo mount ${LOOPBACK}p2 ext_mount/
sudo rsync -axHAXW --progress rootfs/* ext_mount
sync
sudo umount ext_mount
rmdir ext_mount

sudo dd if=sdcard.img of=${SDCARD} bs=2048
sync
sudo rm -f sdcard.img

sudo losetup -d $LOOPBACK