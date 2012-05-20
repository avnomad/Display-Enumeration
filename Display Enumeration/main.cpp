#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <cstdlib>
using std::system;
using std::exit;

#include <windows.h>

#ifdef UNICODE
#define tcout wcout
#else
#define tcout cout
#endif

void displayFields(const DEVMODE &mode,int indent);
void displayFlags(const DISPLAY_DEVICE &,int indent,bool adaptor);

int main()
{
	DWORD n = 0;
	DWORD c;
	DWORD i;
	DISPLAY_DEVICE adapter;
	DISPLAY_DEVICE monitor;
	DEVMODE mode;

	tcout << left;
	ZeroMemory(&adapter,sizeof(DISPLAY_DEVICE));
	adapter.cb = sizeof(DISPLAY_DEVICE);
	while(EnumDisplayDevices(NULL,n,&adapter,0))	// EDD_GET_DEVICE_INTERFACE_NAME
	{											// does the opesite of what stated in documentation!!!
		tcout << TEXT("adapter ") << n << TEXT(":\n");
		tcout << setw(19) << TEXT("  name: ") << adapter.DeviceName << TEXT("\n");
		tcout << setw(19) << TEXT("  description: ") << adapter.DeviceString << TEXT("\n");
		tcout << setw(19) << TEXT("  flags: ") << TEXT("\n");
		displayFlags(adapter,19,false);
		tcout << setw(19) << TEXT("  interface name: ") << adapter.DeviceID << TEXT("\n");
		tcout << setw(19) << TEXT("  key: ") << adapter.DeviceKey << TEXT("\n");

		tcout << setw(19) << TEXT("  modes: ") << TEXT("\n");
		//i = 0;
		//ZeroMemory(&mode,sizeof(mode));
		//mode.dmSize = sizeof(mode);
		//mode.dmDriverExtra = 0;
		//while(EnumDisplaySettingsEx(adapter.DeviceName,i,&mode,0))	// also check with EDS_RAWMODE and EDS_ROTATEDMODE
		//{
		//	tcout << TEXT("    mode ") << i << TEXT(":\n");
		//	displayFields(mode,6);

		//	ZeroMemory(&mode,sizeof(mode));
		//	mode.dmSize = sizeof(mode);
		//	mode.dmDriverExtra = 0;
		//	++i;
		//} // end while
		ZeroMemory(&mode,sizeof(mode));
		mode.dmSize = sizeof(mode);
		mode.dmDriverExtra = 0;
		EnumDisplaySettingsEx(adapter.DeviceName,ENUM_CURRENT_SETTINGS,&mode,0);
		tcout << TEXT("    mode ") << TEXT("ENUM_CURRENT_SETTINGS") << TEXT(":\n");
		displayFields(mode,6);
		ZeroMemory(&mode,sizeof(mode));
		mode.dmSize = sizeof(mode);
		mode.dmDriverExtra = 0;
		EnumDisplaySettingsEx(adapter.DeviceName,ENUM_REGISTRY_SETTINGS,&mode,0);
		tcout << TEXT("    mode ") << TEXT("ENUM_REGISTRY_SETTINGS") << TEXT(":\n");
		displayFields(mode,6);

		tcout << setw(19) << TEXT("  monitors: ") << TEXT("\n");
		c = 0;
		ZeroMemory(&monitor,sizeof(DISPLAY_DEVICE));
		monitor.cb = sizeof(DISPLAY_DEVICE);
		while(EnumDisplayDevices(adapter.DeviceName,c,&monitor,0))
		{
			tcout << TEXT("    monitor ") << c << TEXT(":\n");
			tcout << setw(25) << TEXT("      name: ") << adapter.DeviceName << TEXT("\n");
			tcout << setw(25) << TEXT("      description: ") << adapter.DeviceString << TEXT("\n");
			tcout << setw(25) << TEXT("      flags: ") << TEXT("\n");
			displayFlags(monitor,25,true);
			tcout << setw(25) << TEXT("      interface name: ") << adapter.DeviceID << TEXT("\n");
			tcout << setw(25) << TEXT("      key: ") << adapter.DeviceKey << TEXT("\n");

			tcout << setw(19) << TEXT("      modes: ") << TEXT("\n");
			i = 0;
			ZeroMemory(&mode,sizeof(mode));
			mode.dmSize = sizeof(mode);
			mode.dmDriverExtra = 0;
			while(EnumDisplaySettingsEx(monitor.DeviceName,i,&mode,0))	// also check with EDS_RAWMODE and EDS_ROTATEDMODE
			{
				tcout << TEXT("        mode ") << i << TEXT(":\n");
				displayFields(mode,10);

				ZeroMemory(&mode,sizeof(mode));
				mode.dmSize = sizeof(mode);
				mode.dmDriverExtra = 0;
				++i;
			} // end while
			ZeroMemory(&mode,sizeof(mode));
			mode.dmSize = sizeof(mode);
			mode.dmDriverExtra = 0;
			EnumDisplaySettingsEx(adapter.DeviceName,ENUM_CURRENT_SETTINGS,&mode,0);
			tcout << TEXT("        mode ") << TEXT("ENUM_CURRENT_SETTINGS") << TEXT(":\n");
			displayFields(mode,10);
			ZeroMemory(&mode,sizeof(mode));
			mode.dmSize = sizeof(mode);
			mode.dmDriverExtra = 0;
			EnumDisplaySettingsEx(adapter.DeviceName,ENUM_REGISTRY_SETTINGS,&mode,0);
			tcout << TEXT("        mode ") << TEXT("ENUM_REGISTRY_SETTINGS") << TEXT(":\n");
			displayFields(mode,10);

			tcout << endl;
			++c;
			ZeroMemory(&monitor,sizeof(DISPLAY_DEVICE));
			monitor.cb = sizeof(DISPLAY_DEVICE);
		} // end while

		tcout << endl;
		++n;
		ZeroMemory(&adapter,sizeof(DISPLAY_DEVICE));
		adapter.cb = sizeof(DISPLAY_DEVICE);
	} // end while

	system("pause");
	return 0;
} // end function main


void displayFlags(const DISPLAY_DEVICE &displayDevice,int indent,bool child)
{
	if(displayDevice.StateFlags & DISPLAY_DEVICE_ACTIVE && child)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_ACTIVE\n");
	if(displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP && !child)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_ATTACHED_TO_DESKTOP\n");

	if(displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED && child)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_ATTACHED\n");
	if(displayDevice.StateFlags & DISPLAY_DEVICE_MULTI_DRIVER && !child)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_MULTI_DRIVER\n");

	if(displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_PRIMARY_DEVICE\n");
	if(displayDevice.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_MIRRORING_DRIVER\n");
	if(displayDevice.StateFlags & DISPLAY_DEVICE_VGA_COMPATIBLE)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_VGA_COMPATIBLE\n");
	if(displayDevice.StateFlags & DISPLAY_DEVICE_REMOVABLE)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_REMOVABLE\n");
	if(displayDevice.StateFlags & DISPLAY_DEVICE_MODESPRUNED)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_MODESPRUNED\n");
	if(displayDevice.StateFlags & DISPLAY_DEVICE_REMOTE)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_REMOTE\n");
	if(displayDevice.StateFlags & DISPLAY_DEVICE_DISCONNECT)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_DISCONNECT\n");
	if(displayDevice.StateFlags & DISPLAY_DEVICE_TS_COMPATIBLE)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_TS_COMPATIBLE\n");
	if(displayDevice.StateFlags & DISPLAY_DEVICE_UNSAFE_MODES_ON)
		tcout << setw(indent) << TEXT(' ') << TEXT("DISPLAY_DEVICE_UNSAFE_MODES_ON\n");
} // end function displayFlags


std::ostream &operator<<(std::ostream &out,const POINTL &point)
{
	out << point.x << TEXT(',') << point.y;
	return out;
} // end function operator<<


void displayFields(const DEVMODE &mode,int indent)
{
	const int w = 25;

	tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("device name: ") << mode.dmDeviceName << TEXT("\n");
	tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("specification version: ") << mode.dmSpecVersion << TEXT("\n");
	tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("driver version: ") << mode.dmDriverVersion << TEXT("\n");
	//tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("driver extra: ") << mode.dmDriverExtra << TEXT("\n");
	if(mode.dmFields & DM_ORIENTATION)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmOrientation: ") << mode.dmOrientation << TEXT("\n");
	if(mode.dmFields & DM_PAPERSIZE)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmPaperSize: ") << mode.dmPaperSize << TEXT("\n");
	if(mode.dmFields & DM_PAPERLENGTH)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmPaperLength: ") << mode.dmPaperLength << TEXT("\n");
	if(mode.dmFields & DM_PAPERWIDTH)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmPaperWidth: ") << mode.dmPaperWidth << TEXT("\n");
	if(mode.dmFields & DM_SCALE)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmScale: ") << mode.dmScale << TEXT("\n");
	if(mode.dmFields & DM_COPIES)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmCopies: ") << mode.dmCopies << TEXT("\n");
	if(mode.dmFields & DM_DEFAULTSOURCE)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmDefaultSource: ") << mode.dmDefaultSource << TEXT("\n");
	if(mode.dmFields & DM_PRINTQUALITY)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmPrintQuality: ") << mode.dmPrintQuality << TEXT("\n");
	if(mode.dmFields & DM_POSITION)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmPosition: ") << mode.dmPosition << TEXT("\n");
	if(mode.dmFields & DM_DISPLAYORIENTATION)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmDisplayOrientation: ") << mode.dmDisplayOrientation << TEXT("\n");
	if(mode.dmFields & DM_DISPLAYFIXEDOUTPUT)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmDisplayFixedOutput: ") << mode.dmDisplayFixedOutput << TEXT("\n");
	if(mode.dmFields & DM_COLOR)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmColor: ") << mode.dmColor << TEXT("\n");
	if(mode.dmFields & DM_DUPLEX)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmDuplex: ") << mode.dmDuplex << TEXT("\n");
	if(mode.dmFields & DM_YRESOLUTION)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmYResolution: ") << mode.dmYResolution << TEXT("\n");
	if(mode.dmFields & DM_TTOPTION)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmTTOption: ") << mode.dmTTOption << TEXT("\n");
	if(mode.dmFields & DM_COLLATE)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmCollate: ") << mode.dmCollate << TEXT("\n");
	if(mode.dmFields & DM_FORMNAME)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmFormName: ") << mode.dmFormName << TEXT("\n");
	if(mode.dmFields & DM_LOGPIXELS)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmLogPixels: ") << mode.dmLogPixels << TEXT("\n");
	if(mode.dmFields & DM_BITSPERPEL)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmBitsPerPel: ") << mode.dmBitsPerPel << TEXT("\n");
	if(mode.dmFields & DM_PELSWIDTH)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmPelsWidth: ") << mode.dmPelsWidth << TEXT("\n");
	if(mode.dmFields & DM_PELSHEIGHT)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmPelsHeight: ") << mode.dmPelsHeight << TEXT("\n");
	if(mode.dmFields & DM_DISPLAYFLAGS)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmDisplayFlags: ") << mode.dmDisplayFlags << TEXT("\n");
	if(mode.dmFields & DM_NUP)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmNup: ") << mode.dmNup << TEXT("\n");
	if(mode.dmFields & DM_DISPLAYFREQUENCY)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmDisplayFrequency: ") << mode.dmDisplayFrequency << TEXT("\n");
	if(mode.dmFields & DM_ICMMETHOD)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmICMMethod: ") << mode.dmICMMethod << TEXT("\n");
	if(mode.dmFields & DM_ICMINTENT)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmICMIntent: ") << mode.dmICMIntent << TEXT("\n");
	if(mode.dmFields & DM_MEDIATYPE)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmMediaType: ") << mode.dmMediaType << TEXT("\n");
	if(mode.dmFields & DM_DITHERTYPE)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmDitherType: ") << mode.dmDitherType << TEXT("\n");
	if(mode.dmFields & DM_PANNINGWIDTH)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmPanningWidth: ") << mode.dmPanningWidth << TEXT("\n");
	if(mode.dmFields & DM_PANNINGHEIGHT)
		tcout << setw(indent) << TEXT(' ') << setw(w) << TEXT("dmPanningHeight: ") << mode.dmPanningHeight << TEXT("\n");
} // end function displayFields