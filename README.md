# apple_set_os.efi
Tiny EFI program for unlocking the Intel IGD on the Macbook Pro 11,3 for Linux and Windows.  
It has been made to be easily chainloaded by unmodified EFI bootloader like Grub, rEFInd etc.

The Macbook Pro 11,3 model's EFI is switchting off the Intel GPU if you boot anything but Mac OS X.  
So a little trick by faking the OS identifiction is required to make all hardware accessible.

All credits belong to [Andreas Heider](https://github.com/ah-) who originally discovered this hack:  
https://lists.gnu.org/archive/html/grub-devel/2013-12/msg00442.html

## Usage:
Copy the apple_set_os.efi binary to EFI System Partition (ESP) :
```
mkdir /boot/efi/EFI/custom
cp apple_set_os.efi /boot/efi/EFI/custom
```
ReEFInd should automatically show a new Icon for apple_set_os.efi.

Grub can be configured to start apple_set_os.efi automatically by adding the following lines to  ``/etc/grub.d/40_custom``:
```
search --no-floppy --set=root --label EFI
chainloader (${root})/EFI/custom/apple_set_os.efi
boot
```

