// Copyright (c) 2015 Bruno Bierbaumer

#include <efibind.h>
#include <efidef.h>
#include <efidevp.h>
#include <eficon.h>
#include <efiapi.h>
#include <efierr.h>

#define APPLE_SET_OS_VENDOR  "Apple Inc."
#define APPLE_SET_OS_VERSION "Mac OS X 10.9"

static EFI_GUID APPLE_SET_OS_GUID = { 0xc5c5da95, 0x7d5c, 0x45e6, { 0xb2, 0xf1, 0x3f, 0xd5, 0x2b, 0xb1, 0x00, 0x77 }};

typedef struct efi_apple_set_os_interface {
	UINT64 version;
	EFI_STATUS (EFIAPI *set_os_version) (IN CHAR8 *version);
	EFI_STATUS (EFIAPI *set_os_vendor) (IN CHAR8 *vendor);
} efi_apple_set_os_interface;

EFI_STATUS
efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *systemTable)
{
	SIMPLE_TEXT_OUTPUT_INTERFACE *conOut = systemTable->ConOut;
	conOut->OutputString(conOut, L"apple_set_os started\r\n");

	efi_apple_set_os_interface *set_os = NULL;

	EFI_STATUS status  = systemTable->BootServices->LocateProtocol(&APPLE_SET_OS_GUID, NULL, (VOID**) &set_os);
	if(EFI_ERROR(status) || set_os == NULL) {
		conOut->OutputString(conOut, L"Could not locate the apple set os protocol.\r\n");
		return status;
	}

	if(set_os->version != 0){
		status = set_os->set_os_version((CHAR8 *) APPLE_SET_OS_VERSION);
		if(EFI_ERROR(status)){
			conOut->OutputString(conOut, L"Could not set version.\r\n");
			return status;
		}
		conOut->OutputString(conOut, L"Set os version to " APPLE_SET_OS_VERSION  ".\r\n");
	}

	if(set_os->version == 2){
		status = set_os->set_os_vendor((CHAR8 *) APPLE_SET_OS_VENDOR);  
		if(EFI_ERROR(status)){
			conOut->OutputString(conOut, L"Could not set vendor.\r\n");
			return status;
		}
		conOut->OutputString(conOut, L"Set os vendor to " APPLE_SET_OS_VENDOR  ".\r\n");
	}

	return EFI_SUCCESS;
}
