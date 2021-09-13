
/********************************************
*                                           *
*  Most of this is from Goombi's CipherMii  *
*                                           *
*  Also thanks to Redshyguy's Vapecord for  *
*  the DrawQRCode function and more!        *
*                                           *
*  haha funny header thing go brrrr         *
*                                           *
********************************************/

#include "cheats.hpp"//QR code size: 4 modules, 3 pixels per module, Version 10, else default
#include <stdlib.h>

std::vector<uint8_t> MiiVec;

namespace CTRPluginFramework
{

Handle aptuHandle;

	void DrawQrCode(const Screen& screen, u32 posX, u32 posY, const u8* qrcode) {
		const u32 size_qr = qrcodegen_getSize(qrcode);
		u32 size_qr_s = size_qr;
		u32 size_canvas = size_qr + 8;

	//handle scaling
		u32 scale = 1;
		for(; size_canvas * (scale + 1) < 240; scale++);
		size_qr_s *= scale;
		size_canvas *= scale;

		//screen.DrawRect(posX - 5, posY - 5, size_canvas - 15, size_canvas - 15, Color::White);

		for(u32 y = 0; y <= size_qr_s; y++) {
			for(u32 x = 0; x <= size_qr_s; x++) {
				Color c = qrcodegen_getModule(qrcode, x / scale, y / scale) ? Color::Black : Color::White;
				screen.DrawRect(posX + x, posY + y, scale, scale, c);
			}
		}
	}

Result APT_Wrap(u32 outputSize, u32 inputSize, u32 blockSize, u32 nonceSize, void* input, void* output) {
  u32* cmdbuf=getThreadCommandBuffer();
  cmdbuf[0]=IPC_MakeHeader(0x46,4,4); // 0x470104
  cmdbuf[1]=outputSize;
  cmdbuf[2]=inputSize;
  cmdbuf[3]=blockSize;
  cmdbuf[4]=nonceSize;
  cmdbuf[5]=(inputSize << 4) | 0xA;
  cmdbuf[6]=(u32) input;
  cmdbuf[7]=(outputSize << 4) | 0xC;
  cmdbuf[8]=(u32) output;

  Result ret = 0;
  if(R_FAILED(ret=svcSendSyncRequest(aptuHandle)))
    return ret;

  return cmdbuf[1];
}

int encryptMii(DecMii *data) {
  const Screen& BottomScreen = OSD::GetBottomScreen();
  u8* output = new u8();

//Call APT_Wrap
  if(!R_SUCCEEDED(APT_Wrap(MII_ENCSIZE, MII_DECSIZE, 12, 10, data, output))) {
    OSD::Notify("ERROR: Failed to encrypt the input.");
    return 1;
  }

//Make QR code
  u8 qrcode[qrcodegen_BUFFER_LEN_MAX];
  u8 temp[qrcodegen_BUFFER_LEN_MAX];

  if(qrcodegen_encodeBinary(output, MII_ENCSIZE, qrcode, qrcodegen_Ecc_LOW, 10, 10, qrcodegen_Mask_AUTO, true)) {
	DrawQrCode(BottomScreen, 73, 33, qrcode);
	MessageBox("Here is your QR code.\nIt will disappear when you press \"Ok\"")();
		Sleep(Milliseconds(200));
  }
  delete[] output;
  return 0;
}

void encrypt(void) {
	const Screen& BottomScreen = OSD::GetBottomScreen();
    u8 val;
	std::string name;
    DecMii *data = nullptr;

    srvGetServiceHandle(&aptuHandle, "APT:U");

    if(*(u32 *)0x88B2B28 != 0xFFFFFFFF && (*(u16 *)0x88014D5 == 0)) {
	  if(Process::Read8(0x88014D4, val)) {
	    data = (DecMii *)((0x5C * val) + 0x14895A28);
		Process::ReadString((0x5C * val) + (0x14895A20 + 0x22), name, 20, StringFormat::Utf16);
		Sleep(Milliseconds(100));
	    encryptMii(data);
  	  }
    }

    svcCloseHandle(aptuHandle);
}
void KORencrypt(void) {
	const Screen& BottomScreen = OSD::GetBottomScreen();
    u8 val;
	std::string name;
    DecMii *data = nullptr;

    srvGetServiceHandle(&aptuHandle, "APT:U");

    if (*(u32 *)0x8032218 != 0xFFFFFFFF && (*(u16 *)0x88014D5 == 0)) {
	  if(Process::Read8(0x88014D4, val)) {
	    data = (DecMii *)((0x5C * val) + 0x1488B7A8);
		Process::ReadString((0x5C * val) + (0x1488B7A0 + 0x22), name, 20, StringFormat::Utf16);
		Sleep(Milliseconds(100));
	    encryptMii(data);
  	  }
    }

    svcCloseHandle(aptuHandle);
}
void TWNencrypt(void) {
	const Screen& BottomScreen = OSD::GetBottomScreen();
    u8 val;
	std::string name;
    DecMii *data = nullptr;

    srvGetServiceHandle(&aptuHandle, "APT:U");

    if (*(u32 *)0x8AF73A4 == 0xB88C50 && (*(u16 *)0x88014D5 == 0)) {
	  if(Process::Read8(0x88014D4, val)) {
	    data = (DecMii *)((0x5C * val) + 0x1488B928);
		Process::ReadString((0x5C * val) + (0x1488B920 + 0x22), name, 20, StringFormat::Utf16);
		Sleep(Milliseconds(100));
	    encryptMii(data);
  	  }
    }

    svcCloseHandle(aptuHandle);
}
}