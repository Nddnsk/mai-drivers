# Задание
Собрать конфигурацию buildroot

## Клонирую buildroot и делаю checkout
```
git clone https://git.buildroot.net/buildroot
git checkout 2025.02.8
```
## Запускаю сборку
```
make beaglebone_defconfig
make menuconfig
```

## Изменяю конфигурацию buildroot
`Buildroot toolchain" -> "External toolchain`

`Root password: "admin"`

`Custom tarball" -> "Latest Version (6.12)`

`bb.org" -> "omap2plus`

## Запускаю окнфигурацию ядра
```
make linux-menuconfig
```

## Далее компиляция
```
make
```
## Смотрю файлы
```
vboxuser:~/MAI_linux_drivers/lab2$ ls output/images
am335x-boneblack.dtb           am335x-bone.dtb                am335x-evm.dtb    extlinux     rootfs.ext4  u-boot.img
am335x-boneblack-wireless.dtb  am335x-bonegreen.dtb           am335x-evmsk.dtb  MLO          rootfs.tar   uEnv.txt
am335x-boneblue.dtb            am335x-bonegreen-wireless.dtb  boot.vfat         rootfs.ext2  sdcard.img   zImage
```