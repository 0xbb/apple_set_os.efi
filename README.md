# apple_set_os.efi
Tiny EFI program for unlocking the Intel IGD on the Macbook Pro 11,3 for Linux and Windows.  

The Macbook Pro 11,3 model's EFI is switchting off the Intel GPU if you boot anything but Mac OS X.  
So a little trick by faking the OS identifiction is required to make all hardware accessible.

All credits belong to [Andreas Heider](/ah-) who originally discovered this hack:  
https://lists.gnu.org/archive/html/grub-devel/2013-12/msg00442.html

## Usage:
Copy apple_set_os.efi to EFI System Partition (ESP) 
```
mkdir /boot/efi/EFI/tools
cp apple_set_os.efi /boot/efi/EFI/tools
```

The EFI program can then be chainloaded by any EFI bootloader like Grub, rEFInd etc.

For Grub the following entry in ``40_custom`` can be used to chainload apple_set_os.efi every start:
```
search --no-floppy --set=root --label EFI
chainloader (${root})/EFI/tools/apple_set_os.efi
boot
```

