// SDK for EverEdit
// Copyright ?2011-2013 everedit.net, All Rights Reserved.
//
// ���������Ҫʵ��EE_PluginInit, ���򲻼���
// DWORD EE_PluginInit(EE_Context* pContext);
// DWORD EE_PluginUninit();
// DWORD EE_PluginInfo(wchar_t* lpText, int nLength);
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 * 2013/01/10 First Version
*******************************************************************************/

#ifndef __EESDK_HPP__
#define __EESDK_HPP__

#include "eecore.h"

//******************************************************************************
// Messages

/**
 * @Return: (HWND)��ȡ��ǰ������ı��ĵ�
 */
#define EEM_GETACTIVETEXT           WM_USER+3000

/**
 * @Return: (HWND)��ȡ��ǰ�����HEX�ĵ�
 */
#define EEM_GETACTIVEHEX            WM_USER+3001

/**
 * @Msg:    ��ָ�����ļ�
 * @Return: (HWND)��ʾ���ļ��Ĵ���
 * @wparam: (const wchar_t*)�ļ���ȫ·��
 * @lparam: (EE_LoadFile)
 */
#define EEM_LOADFILE                WM_USER+3002

/**
 * @Msg:    �趨���ֻص�����,�����������/ɾ��Hook
 * @Return: (int)�ص���������
 * @wparam: (int)�ص�������ö��ֵ
 * @lparam: (LPVOID)�ص�������ַ
 */
#define EEM_SETHOOK                 WM_USER+3003

/**
 * @Msg:    ���DockingWindow
 * @Return: (BOOL)
 * @wparam: (BOOL)true:���,false:ɾ��
 * @lparam: (EE_DockingWindow*)
 */
#define EEM_DOCKINGWINDOW           WM_USER+3004

/**
 * @Msg:    ���/ɾ��/���½���Ԫ��״̬
 * @Return: (void)
 * @wparam: (int)����
 * @lparam: (EE_UpdateUIElement*)Ԫ��״̬,����nUpdate����ָ��
 */
#define EEM_UPDATEUIELEMENT         WM_USER+3004

/**
 * @Msg:    ��ȡһ���б�,���б�������е�text���ڵľ��,ע��:�����߱����ֹ�����(delete[] list)
 * @Return: (HWND*)�б��׵�ַ
 * @wparam: (int*)���ܸ����ĵ�ַ
 */
#define EEM_GETHWNDLIST             WM_USER+3005

/**
 * @Msg:    ����һ������ͼ����
 * @Return: (BOOL)True:�ô��ڴ����ұ��ɹ�����Ϊ����, ����Ϊ:False
 * @wparam: (HWND�Ӵ��ڵľ��
 */
#define EEM_SETACTIVEVIEW           WM_USER+3006

/**
 * @Msg:    ������Ӹ��ֻص�����
 * @Return: (int)�ص���������
 * @wparam: (int)������ʼ��ַ(EE_HookFunc*)
 * @lparam: (int)�������
 */
#define EEM_SETHOOKS                WM_USER+3007


/**
 * @Msg:    �ָ�DockingWindow��λ����Ϣ. ����Ϣ������ʱ��ϵͳ�Զ�����, �û����ɵ���!
 * @Return: (HWND)������Ч�Ĵ�����Ϣ
 * @wparam: (const wchar_t*)��DockingWindow��Caption
 */
#define EEM_RESOTREDOCKINGWINDOW    WM_USER+1211


//******************************************************************************

// EE_LoadFile.nViewType
#define WT_UNKNOWN                    0
#define WT_TEXT                       1
#define WT_HEX                        2

//EE_UpdateUIElementn.Action
#define EE_UI_REMOVE                  0
#define EE_UI_ADD                     1
#define EE_UI_ENABLE                  2
#define EE_UI_SETCHECK                3

//******************************************************************************
// ���ֻص�����ԭ��˵��

// ɾ��ָ���Ļص�����
#define EEHOOK_REMOVE                 0

// int(HWND, HMENU, int, int)
#define EEHOOK_TEXTMENU               1

// int(HWND, HMENU, int, int)
#define EEHOOK_HEXMENU                2

// int(HWND)
#define EEHOOK_PRESAVE                3

// int(HWND)
#define EEHOOK_POSTSAVE               4

// int(HWND)
#define EEHOOK_PRECLOSE               5

// int(HWND)
#define EEHOOK_POSTCLOSE              6

// int(HWND, WPARAM, LPARAM)
#define EEHOOK_APPMSG                 7

// int(HWND)
#define EEHOOK_IDLE                   8

// int(MSG*)
#define EEHOOK_PRETRANSLATEMSG        9

// int(RECT*)
#define EEHOOK_APPRESIZE              10

// int(HWND)
#define EEHOOK_APPACTIVATE            11

// int(HWND old, HWND new)
#define EEHOOK_CHILDACTIVE            12

// int(const wchar_t*, int)
#define EEHOOK_RUNCOMMAND             13

// int(const wchar_t*LPVOID)
#define EEHOOK_PRELOAD                14

// int(const wchar_t*LPVOID)
#define EEHOOK_POSTLOAD               15

// int(HWND)
#define EEHOOK_POSTNEWTEXT            16

// int(HMENU, int, int)
#define EEHOOK_TABMENU                17

// int(int, HWND, HICON*)
#define EEHOOK_VIEWICON               18

// int(HWND, wchar_t*)
#define EEHOOK_TEXTCHAR               100

// int(HWND, WPARAM, LPARAM)
#define EEHOOK_TEXTCOMMAND            101

// int(HWND, ECNMHDR_TextUpdate*)
#define EEHOOK_UPDATETEXT             102

// int(HWND, ECNMHDR_CaretChange*)
#define EEHOOK_TEXTCARETCHANGE        103

// AutoWordList*(HWND, AutoWordInput*)
#define EEHOOK_PREWORDCOMPLETE        104

// int(int, LPCTSTR, int)
#define EEHOOK_POSTWORDCOMPLETE       105

// int()
#define EEHOOK_CLOSEWORDCOMPLETE      106

// int(HWND, wchar_t)
#define EEHOOK_HEXCHAR                200


// �������ش���Ϣ��ʾ���ټ�����������callback·��, magic value
#define EEHOOK_RET_DONTROUTE          0xBC614E

//******************************************************************************
// ����ú����ͽṹ��

//��������Ϣ
struct EE_Context
{
    HWND hMain;
    HWND hToolBar;
    HWND hStatusBar;
    HWND hClient;
    HWND hStartPage;
    HMENU hMainMenu;
    HMENU hPluginMenu;
    DWORD* pCommand;
    DWORD dwVersion;
    DWORD dwBuild;
    LCID dwLCID;
};

//�����������Hook
struct EE_HookFunc
{
	int nType;
 	LPVOID lpFunc;
};

// Messages
struct EE_LoadFile
{
    int nCodepage;
    int nViewType;
    BOOL bReadOnly;
};

//����Ԫ�ظ���
struct EE_UpdateUIElement
{
    int nAction;
    int nValue;
};

// ����ͣ����λ��
#define EE_DOCK_LEFT                0
#define EE_DOCK_TOP                 1
#define EE_DOCK_RIGHT               2
#define EE_DOCK_BOTTOM              3
#define EE_DOCK_FLOAT               4

#define EE_DOCK_NOLEFT              (1<<EE_DOCK_LEFT)
#define EE_DOCK_NOTOP               (1<<EE_DOCK_TOP)
#define EE_DOCK_NORIGHT             (1<<EE_DOCK_RIGHT)
#define EE_DOCK_NOBOTTOM            (1<<EE_DOCK_BOTTOM)

struct EE_DockingWindow
{
    HWND hWnd;
    BOOL bDestroyOnClose;
    int nSide; 
};


//�Զ����ʱ�û��������ʾ�ı���Ϣ
struct AutoWordInput
{
    EC_Pos* pos;
    const wchar_t* lpHintText;
    int nLength;
};

//������ص��Զ������Ϣ
struct AutoWordList
{
    wchar_t** lpWords;
    int nCount;
    HICON hIcon;
    DWORD id;
};


#endif //__EESDK_HPP__

