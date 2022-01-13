// main.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <fstream>
#include <windows.h>
#include <shobjidl_core.h>
#include <vector>
// Header required to help detect window version
#include <sdkddkver.h>
// Macro used to reduce namespace pollution
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
// Header needed for unicode adjustment support
#include <tchar.h>
#include "dirent.h"
#include<urlmon.h>
#pragma comment (lib,"urlmon.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define ID_DEFAULTPROGRESSCTRL	401

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("MiichanicToolBoxInstaller");//class name, make this your own

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Miichanic's Tool Box Installer v2.00");//title name, make this your own

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LPWSTR PickContainer()//https://stackoverflow.com/q/8269696
{
    LPWSTR g_path = (LPWSTR)"";
    IFileDialog* pfd;
    if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd))))
    {
        DWORD dwOptions;
        if (SUCCEEDED(pfd->GetOptions(&dwOptions)))
        {
            pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
        }
        if (SUCCEEDED(pfd->Show(NULL)))
        {
            IShellItem* psi;
            if (SUCCEEDED(pfd->GetResult(&psi)))
            {
                if (!SUCCEEDED(psi->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &g_path)))
                {
                    //MessageBox(NULL, TEXT("GetIDListName() failed"), NULL, NULL);
                    return (LPWSTR)"";
                }
                psi->Release();
            }
        }
        pfd->Release();
    }
    return g_path;
}

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

std::vector<std::string> getListOfDrives() {//https://stackoverflow.com/questions/286534/enumerating-all-available-drive-letters-in-windows
    std::vector<std::string> arrayOfDrives;
    char* szDrives = new char[MAX_PATH]();
    GetLogicalDriveStringsA(MAX_PATH, szDrives);
    for (int i = 0; i < 100; i += 4)
        if (szDrives[i] != (char)0)
            arrayOfDrives.push_back(std::string{ szDrives[i],szDrives[i + 1],szDrives[i + 2] });
    delete[] szDrives;
    return arrayOfDrives;
}

std::string detect3dsSd() {
    DIR* dir;//https://stackoverflow.com/a/612176
    struct dirent* ent;
    std::vector<std::string> drives = getListOfDrives();

    for (std::string currentDrive : drives) {
        if ((dir = opendir(currentDrive.c_str())) != NULL) {
            /* print all the files and directories within directory */
            while ((ent = readdir(dir)) != NULL) {
                if (strstr(ent->d_name, "Nintendo 3DS")) {
                    return currentDrive;
                }
            }
            closedir(dir);
        }
    }
    return "";
}

std::string getDrivename(std::string Drive) {
    std::wstring stemp = s2ws(Drive);
    LPCWSTR result = stemp.c_str();
    WCHAR szVolumeName[MAX_PATH];
    BOOL bSucceeded = GetVolumeInformationW(result, szVolumeName, MAX_PATH, NULL, NULL, NULL, NULL, 0);
    std::wstring wstr = std::wstring(szVolumeName);
    std::string out(wstr.begin(), wstr.end());
    return out;
}


int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Error"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 450,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Error"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
//make handles to do whatever with. We're having spaghetti for dinner.
//i guess you could really just make as many as you need
HWND item1, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12, item13/*, item14, item15*/;
int page = 0;//page index
std::string realdir;//drive to install to

bool Region[6] = {//maybe remove some of these, meh
    false,//jpn (0)
    false,//usa (1)
    false,//eur (2)
    false,//chn (3)
    false,//kor (4)
    false,//twn (5)
};

void disableAll() {
    EnableWindow(item1, false);//disable all buttons
    EnableWindow(item3, false);
    EnableWindow(item4, false);
    EnableWindow(item5, false);
    EnableWindow(item6, false);
    EnableWindow(item7, false);
    EnableWindow(item8, false);
    EnableWindow(item9, false);
    EnableWindow(item12, false);
}

void enableAll() {
    EnableWindow(item1, true);//disable all buttons
    EnableWindow(item3, true);
    EnableWindow(item4, true);
    EnableWindow(item5, true);
    EnableWindow(item6, true);
    EnableWindow(item7, true);
    EnableWindow(item8, true);
    EnableWindow(item9, true);
    EnableWindow(item12, true);
}
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //edit this stuff
    std::string TIDJPN = "0004001000020700";
    std::string TIDUSA = "0004001000021700";
    std::string TIDEUR = "0004001000022700";
    std::string TIDCHN = "0004001000026700";
    std::string TIDKOR = "0004001000027700";
    std::string TIDTWN = "0004001000028700";
    LPCTSTR PluginLink = TEXT("https://github.com/FoofooTheGuy/Miichanic_Plugin/releases/latest/download/Miichanic.3gx");
    LPCTSTR PluginFile = TEXT("Miichanic.3gx");
    std::string PluginFileString = "Miichanic.3gx";
    LPCTSTR BootFirmLink = TEXT("https://github.com/FoofooTheGuy/Miichanic_Plugin/raw/main/boot.firm");

    BOOL checked1 = IsDlgButtonChecked(hwnd, 2);
    BOOL checked2 = IsDlgButtonChecked(hwnd, 3);
    BOOL checked3 = IsDlgButtonChecked(hwnd, 4);
    BOOL checked4 = IsDlgButtonChecked(hwnd, 5);
    BOOL checked5 = IsDlgButtonChecked(hwnd, 6);
    BOOL checked6 = IsDlgButtonChecked(hwnd, 7);
    static HBRUSH hbrush = NULL;
    //BOOL checked2 = IsDlgButtonChecked(hwnd, 5);
    std::string _3DSDIR;
    std::wstring _3dsdirw;
    LPCWSTR LPCDIR;
    std::string command;
    HRESULT hr;
    HRESULT choice;
    switch (message)
    {
    case WM_CREATE:
        case 0:
        {
            item1 = CreateWindow(TEXT("BUTTON"), TEXT("Install!"), WS_VISIBLE | WS_CHILD | WS_BORDER, 15, 285, 450, 30, hwnd, (HMENU)1, NULL, NULL);
            if (detect3dsSd() != "") {
                _3DSDIR = detect3dsSd() + " (" + getDrivename(detect3dsSd()) + ")";
                _3dsdirw = s2ws(_3DSDIR);//bruh
                LPCDIR = _3dsdirw.c_str();
                realdir = detect3dsSd();
                EnableWindow(item1, true);
            }
            else {
                EnableWindow(item1, false);
                _3dsdirw = s2ws("Failed to detect SD card");//bruh
                LPCDIR = _3dsdirw.c_str();
            }
            //https://github.com/malortie/Tutorials/blob/master/tutorials/cpp/win32/controls/progressbar/ProgressBar.cpp
            item2 = CreateWindowEx(0, PROGRESS_CLASS, TEXT(""), WS_CHILD | WS_VISIBLE, 15, 320, 450, 30, hwnd, (HMENU)ID_DEFAULTPROGRESSCTRL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            item3 = CreateWindow(TEXT("BUTTON"), TEXT("JPN"), WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CHECKBOX, 20, 30, 185, 35, hwnd, (HMENU)2, ((LPCREATESTRUCT)lParam)->hInstance, NULL);//region buttons, note some out if you dont need some
            item4 = CreateWindow(TEXT("BUTTON"), TEXT("USA"), WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CHECKBOX, 20, 70, 185, 35, hwnd, (HMENU)3, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            item5 = CreateWindow(TEXT("BUTTON"), TEXT("EUR"), WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CHECKBOX, 20, 110, 185, 35, hwnd, (HMENU)4, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            item6 = CreateWindow(TEXT("BUTTON"), TEXT("CHN"), WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CHECKBOX, 20, 150, 185, 35, hwnd, (HMENU)5, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            item7 = CreateWindow(TEXT("BUTTON"), TEXT("KOR"), WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CHECKBOX, 20, 190, 185, 35, hwnd, (HMENU)6, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            item8 = CreateWindow(TEXT("BUTTON"), TEXT("TWN"), WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CHECKBOX, 20, 230, 185, 35, hwnd, (HMENU)7, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            item9 = CreateWindow(TEXT("BUTTON"), LPCDIR, WS_VISIBLE | WS_CHILD | WS_BORDER, 235, 130, 200, 25, hwnd, (HMENU)8, NULL, NULL);
            item10 = CreateWindow(TEXT("STATIC"), TEXT("Region:"), WS_VISIBLE | WS_CHILD, 86, 6, 52, 20, hwnd, NULL, NULL, NULL);
            item11 = CreateWindow(TEXT("STATIC"), TEXT("Installation drive:"), WS_VISIBLE | WS_CHILD, 279, 6, 113, 20, hwnd, NULL, NULL, NULL);
            item12 = CreateWindow(TEXT("BUTTON"), TEXT("Refresh"), WS_VISIBLE | WS_CHILD | WS_BORDER, 305, 100, 60, 25, hwnd, (HMENU)9, NULL, NULL);
            item13 = CreateWindow(TEXT("STATIC"), TEXT("Choose options, then click \"Install!\" when you're ready."), WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 357, 440, 30, hwnd, NULL, NULL, NULL);
        }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
            case 1://Install!
            {
                hr = GetDriveTypeA(realdir.c_str());
                switch (hr)
                {
                    case DRIVE_UNKNOWN: ::MessageBox(hwnd, TEXT("Selected drive Unknown."), TEXT("Error"), MB_ICONERROR);
                        return 0;
                        break;
                    case DRIVE_NO_ROOT_DIR: ::MessageBox(hwnd, TEXT("Selected drive Not found."), TEXT("Error"), MB_ICONERROR);
                        return 0;
                        break;
                    case DRIVE_REMOVABLE: break;
                    case DRIVE_FIXED: 
                        choice = ::MessageBox(hwnd, TEXT("Warning: Installation might not succeed if this is not running in administrator mode!"), TEXT("Drive Protection Problem"), MB_OKCANCEL | MB_ICONEXCLAMATION);
                        switch (choice) {
                            case IDOK: break;
                            default: 
                                return 0;
                                break;
                        }
                        break;
                    case DRIVE_REMOTE: ::MessageBox(hwnd, TEXT("Remote drives not supported. (yet?)"), TEXT("Error"), MB_ICONERROR);
                        return 0;
                        break;
                    case DRIVE_CDROM: ::MessageBox(hwnd, TEXT("Cannot write to CD ROM"), TEXT("Error"), MB_ICONERROR);
                        return 0;
                        break;
                    case DRIVE_RAMDISK: break;
                    default: ::MessageBox(hwnd, TEXT("Unknown Error"), TEXT("Error"), MB_ICONERROR);
                        return 0;
                        break;
                }
                SendMessage(item13, WM_SETTEXT, 0, (LPARAM)TEXT("Starting..."));
                disableAll();
                SendMessage(item13, WM_SETTEXT, 0, (LPARAM)TEXT("Downloading Miichanic.3gx..."));//you may want to change this
                hr = URLDownloadToFile(NULL, PluginLink, PluginFile, 0, NULL);
                switch (hr)//http://www.cplusplus.com/forum/windows/53113/#msg288171
                {
                case S_OK: break;
                case INET_E_DOWNLOAD_FAILURE: ::MessageBox(hwnd, TEXT("Failed to get server data."), TEXT("Error 1"), MB_ICONERROR); break;
                case E_OUTOFMEMORY: ::MessageBox(hwnd, TEXT("Failed to save file."), TEXT("Error 2"), MB_ICONERROR); break;
                default: ::MessageBox(hwnd, TEXT("Failed to download file."), TEXT("Error 3"), MB_ICONERROR);
                }
                ::SendMessage(item2, PBM_SETPOS, (WPARAM)(INT)25, 0);//make progress bar 25
                SendMessage(item13, WM_SETTEXT, 0, (LPARAM)TEXT("Downloading boot.firm..."));
                hr = URLDownloadToFile(NULL, BootFirmLink, _T("boot.firm"), 0, NULL);
                switch (hr)//http://www.cplusplus.com/forum/windows/53113/#msg288171
                {
                case S_OK: break;
                case INET_E_DOWNLOAD_FAILURE: ::MessageBox(hwnd, TEXT("Failed to get server data."), TEXT("Error 1"), MB_ICONERROR); break;
                case E_OUTOFMEMORY: ::MessageBox(hwnd, TEXT("Failed to save file."), TEXT("Error 2"), MB_ICONERROR); break;
                default: ::MessageBox(hwnd, TEXT("Failed to download file."), TEXT("Error 3"), MB_ICONERROR);
                }
                ::SendMessage(item2, PBM_SETPOS, (WPARAM)(INT)50, 0);//make progress bar 50
                SendMessage(item13, WM_SETTEXT, 0, (LPARAM)TEXT("Copying to drive..."));
                if (Region[0]) {//jpn
                    std::string MakedirCom("md " + realdir + "luma\\plugins\\" + TIDJPN);
                    std::string FinalPath("copy " + PluginFileString + " " + realdir + "luma\\plugins\\" + TIDJPN + "\\" + PluginFileString);
                    system(MakedirCom.c_str());
                    system(FinalPath.c_str());
                }
                if (Region[1]) {//usa
                    std::string MakedirCom("md " + realdir + "luma\\plugins\\" + TIDUSA);
                    std::string FinalPath("copy " + PluginFileString + " " + realdir + "luma\\plugins\\" + TIDUSA + "\\" + PluginFileString);
                    system(MakedirCom.c_str());
                    system(FinalPath.c_str());
                }
                if (Region[2]) {//eur
                    std::string MakedirCom("md " + realdir + "luma\\plugins\\" + TIDEUR);
                    std::string FinalPath("copy " + PluginFileString + " " + realdir + "luma\\plugins\\" + TIDEUR + "\\" + PluginFileString);
                    system(MakedirCom.c_str());
                    system(FinalPath.c_str());
                }
                if (Region[3]) {//chn
                    std::string MakedirCom("md " + realdir + "luma\\plugins\\" + TIDCHN);
                    std::string FinalPath("copy " + PluginFileString + " " + realdir + "luma\\plugins\\" + TIDCHN + "\\" + PluginFileString);
                    system(MakedirCom.c_str());
                    system(FinalPath.c_str());
                }
                if (Region[4]) {//kor
                    std::string MakedirCom("md " + realdir + "luma\\plugins\\" + TIDKOR);
                    std::string FinalPath("copy " + PluginFileString + " " + realdir + "luma\\plugins\\" + TIDKOR + "\\" + PluginFileString);
                    system(MakedirCom.c_str());
                    system(FinalPath.c_str());
                }
                if (Region[5]) {//twn
                    std::string MakedirCom("md " + realdir + "luma\\plugins\\" + TIDTWN);
                    std::string FinalPath("copy " + PluginFileString + " " + realdir + "luma\\plugins\\" + TIDTWN + "\\" + PluginFileString);
                    system(MakedirCom.c_str());
                    system(FinalPath.c_str());
                }
                ::SendMessage(item2, PBM_SETPOS, (WPARAM)(INT)75, 0);//make progress bar 75
                std::string FinalPath("copy boot.firm " + realdir);
                system(FinalPath.c_str());
                remove(PluginFileString.c_str());//delete downloaded files after copying
                remove("boot.firm");
                ::SendMessage(item2, PBM_SETPOS, (WPARAM)(INT)100, 0);//make progress bar 100
                SendMessage(item13, WM_SETTEXT, 0, (LPARAM)TEXT("Installation complete!"));
                    choice = ::MessageBox(hwnd, TEXT("Installation complete! Would you like to continue to the rest of the guide?"), TEXT("Complete!"), MB_YESNO | MB_ICONASTERISK);
                    switch (choice) {
                    case IDYES: system("start \"\" https://github.com/FoofooTheGuy/Miichanic_Plugin#method-1-assisted-installation-using-a-windows-pc");//change this as well
                        break;
                    default:
                        break;
                    }
                    ::SendMessage(item2, PBM_SETPOS, (WPARAM)(INT)0, 0);//make progress bar 0
                    enableAll();
                    SendMessage(item13, WM_SETTEXT, 0, (LPARAM)TEXT("Choose options, then click \"Install!\" when you're ready."));
            }
                break;
            case 2://JPN
                if (checked1) {
                    CheckDlgButton(hwnd, 2, BST_UNCHECKED);
                    Region[0] = false;
                }
                else {
                    CheckDlgButton(hwnd, 2, BST_CHECKED);
                    Region[0] = true;
                }
                //MessageBeep(MB_OK);
                break;
            case 3://USA
                if (checked2) {
                    CheckDlgButton(hwnd, 3, BST_UNCHECKED);
                    Region[1] = false;
                }
                else {
                    CheckDlgButton(hwnd, 3, BST_CHECKED);
                    Region[1] = true;
                }
                //MessageBeep(MB_OK);
                break;
            case 4://EUR
                if (checked3) {
                    CheckDlgButton(hwnd, 4, BST_UNCHECKED);
                    Region[2] = false;
                }
                else {
                    CheckDlgButton(hwnd, 4, BST_CHECKED);
                    Region[2] = true;
                }
                //MessageBeep(MB_OK);
                break;
            case 5://CHN
                if (checked4) {
                    CheckDlgButton(hwnd, 5, BST_UNCHECKED);
                    Region[3] = false;
                }
                else {
                    CheckDlgButton(hwnd, 5, BST_CHECKED);
                    Region[3] = true;
                }
                //MessageBeep(MB_OK);
                break;
            case 6://KOR
                if (checked5) {
                    CheckDlgButton(hwnd, 6, BST_UNCHECKED);
                    Region[4] = false;
                }
                else {
                    CheckDlgButton(hwnd, 6, BST_CHECKED);
                    Region[4] = true;
                }
                //MessageBeep(MB_OK);
                break;
            case 7://TWN
                if (checked6) {
                    CheckDlgButton(hwnd, 7, BST_UNCHECKED);
                    Region[5] = false;
                }
                else {
                    CheckDlgButton(hwnd, 7, BST_CHECKED);
                    Region[5] = true;
                }
                //MessageBeep(MB_OK);
                break;
            case 8://drive
            {
                LPWSTR drive = PickContainer();
                if (drive != (LPCWSTR)"") {
                    std::wstring wdrive(drive);
                    wdrive = wdrive.substr(0, 3);
                    std::string out(wdrive.begin(), wdrive.end());
                    _3DSDIR = out + " (" + getDrivename(out) + ")";
                    _3dsdirw = s2ws(_3DSDIR);
                    LPCDIR = _3dsdirw.c_str();
                    realdir = out;
                    std::wstring realdirw = s2ws(realdir);
                    //::MessageBox(hwnd, realdirw.c_str(), TEXT("Error 3"), MB_ICONERROR);
                    SendMessage(item9, WM_SETTEXT, 0, (LPARAM)LPCDIR);
                    //MessageBox(hwnd, LPCDIR, TEXT("here dir"), MB_ICONEXCLAMATION);
                    EnableWindow(item1, true);
                }
            }
                break;
            case 9://Refresh
                if (detect3dsSd() != "") {
                    _3DSDIR = detect3dsSd() + " (" + getDrivename(detect3dsSd()) + ")";
                    _3dsdirw = s2ws(_3DSDIR);//bruh
                    LPCDIR = _3dsdirw.c_str();
                    realdir = detect3dsSd();
                    EnableWindow(item1, true);
                }
                else {
                    EnableWindow(item1, false);
                    _3dsdirw = s2ws("Failed to detect SD card");//bruh
                    LPCDIR = _3dsdirw.c_str();
                }
                SendMessage(item9, WM_SETTEXT, 0, (LPARAM)LPCDIR);
                break;
        }
        break;
    case WM_CTLCOLORSTATIC://https://stackoverflow.com/a/51376518
    {
        HDC hdcStatic = (HDC)wParam;
        if (lParam == (LPARAM)item10)
        {
            SetTextColor(hdcStatic, RGB(0, 0, 0));
            SetBkColor(hdcStatic, RGB(255, 255, 255));
            if (!hbrush)
                hbrush = CreateSolidBrush(RGB(255, 255, 255));
            return (LRESULT)hbrush;
        }
        break;
    }
    case WM_DESTROY:
        if (hbrush) DeleteObject(hbrush);
        hbrush = NULL;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
        break;
    }

    return 0;
}