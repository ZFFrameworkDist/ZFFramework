/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFImpl_sys_Qt_ZFUIKit_impl.h"

#include "ZFUIKit.h"

#if ZF_ENV_sys_Qt

#include <QKeyEvent>

ZFUIKeyCodeEnum ZFUIViewImpl_sys_Qt_ZFUIKeyCodeFromQKeyCode(int qKeyCode)
{
    switch(qKeyCode)
    {
        case Qt::Key_Escape:
            return ZFUIKeyCode::e_kEsc;
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            return ZFUIKeyCode::e_kTab;
        case Qt::Key_Backspace:
            return ZFUIKeyCode::e_kBackspace;
        case Qt::Key_Return:
            return ZFUIKeyCode::e_kEnter;
        case Qt::Key_Space:
            return ZFUIKeyCode::e_kSpace;
        case Qt::Key_CapsLock:
            return ZFUIKeyCode::e_kCapsLock;
        case Qt::Key_Shift:
            return ZFUIKeyCode::e_kShift;
        case Qt::Key_Control:
            return ZFUIKeyCode::e_kCtrl;
        case Qt::Key_Alt:
            return ZFUIKeyCode::e_kAlt;
        case Qt::Key_Meta:
            return ZFUIKeyCode::e_kCommand;
        case Qt::Key_Menu:
            return ZFUIKeyCode::e_kContextMenu;

        case Qt::Key_F1:
            return ZFUIKeyCode::e_kF1;
        case Qt::Key_F2:
            return ZFUIKeyCode::e_kF2;
        case Qt::Key_F3:
            return ZFUIKeyCode::e_kF3;
        case Qt::Key_F4:
            return ZFUIKeyCode::e_kF4;
        case Qt::Key_F5:
            return ZFUIKeyCode::e_kF5;
        case Qt::Key_F6:
            return ZFUIKeyCode::e_kF6;
        case Qt::Key_F7:
            return ZFUIKeyCode::e_kF7;
        case Qt::Key_F8:
            return ZFUIKeyCode::e_kF8;
        case Qt::Key_F9:
            return ZFUIKeyCode::e_kF9;
        case Qt::Key_F10:
            return ZFUIKeyCode::e_kF10;
        case Qt::Key_F11:
            return ZFUIKeyCode::e_kF11;
        case Qt::Key_F12:
            return ZFUIKeyCode::e_kF12;

        case Qt::Key_0:
            return ZFUIKeyCode::e_k0;
        case Qt::Key_1:
            return ZFUIKeyCode::e_k1;
        case Qt::Key_2:
            return ZFUIKeyCode::e_k2;
        case Qt::Key_3:
            return ZFUIKeyCode::e_k3;
        case Qt::Key_4:
            return ZFUIKeyCode::e_k4;
        case Qt::Key_5:
            return ZFUIKeyCode::e_k5;
        case Qt::Key_6:
            return ZFUIKeyCode::e_k6;
        case Qt::Key_7:
            return ZFUIKeyCode::e_k7;
        case Qt::Key_8:
            return ZFUIKeyCode::e_k8;
        case Qt::Key_9:
            return ZFUIKeyCode::e_k9;

        case Qt::Key_A:
            return ZFUIKeyCode::e_kA;
        case Qt::Key_B:
            return ZFUIKeyCode::e_kB;
        case Qt::Key_C:
            return ZFUIKeyCode::e_kC;
        case Qt::Key_D:
            return ZFUIKeyCode::e_kD;
        case Qt::Key_E:
            return ZFUIKeyCode::e_kE;
        case Qt::Key_F:
            return ZFUIKeyCode::e_kF;
        case Qt::Key_G:
            return ZFUIKeyCode::e_kG;
        case Qt::Key_H:
            return ZFUIKeyCode::e_kH;
        case Qt::Key_I:
            return ZFUIKeyCode::e_kI;
        case Qt::Key_J:
            return ZFUIKeyCode::e_kJ;
        case Qt::Key_K:
            return ZFUIKeyCode::e_kK;
        case Qt::Key_L:
            return ZFUIKeyCode::e_kL;
        case Qt::Key_M:
            return ZFUIKeyCode::e_kM;
        case Qt::Key_N:
            return ZFUIKeyCode::e_kN;
        case Qt::Key_O:
            return ZFUIKeyCode::e_kO;
        case Qt::Key_P:
            return ZFUIKeyCode::e_kP;
        case Qt::Key_Q:
            return ZFUIKeyCode::e_kQ;
        case Qt::Key_R:
            return ZFUIKeyCode::e_kR;
        case Qt::Key_S:
            return ZFUIKeyCode::e_kS;
        case Qt::Key_T:
            return ZFUIKeyCode::e_kT;
        case Qt::Key_U:
            return ZFUIKeyCode::e_kU;
        case Qt::Key_V:
            return ZFUIKeyCode::e_kV;
        case Qt::Key_W:
            return ZFUIKeyCode::e_kW;
        case Qt::Key_X:
            return ZFUIKeyCode::e_kX;
        case Qt::Key_Y:
            return ZFUIKeyCode::e_kY;
        case Qt::Key_Z:
            return ZFUIKeyCode::e_kZ;

        case Qt::Key_Agrave:
            return ZFUIKeyCode::e_kGrave;
        case Qt::Key_Minus:
            return ZFUIKeyCode::e_kMinus;
        case Qt::Key_Equal:
            return ZFUIKeyCode::e_kEquals;
        case Qt::Key_BracketLeft:
            return ZFUIKeyCode::e_kBracketLeft;
        case Qt::Key_BracketRight:
            return ZFUIKeyCode::e_kBracketRight;
        case Qt::Key_Backslash:
            return ZFUIKeyCode::e_kBackSlash;
        case Qt::Key_Semicolon:
            return ZFUIKeyCode::e_kSemiColon;
        case Qt::Key_Apostrophe:
            return ZFUIKeyCode::e_kApostrophe;
        case Qt::Key_Comma:
            return ZFUIKeyCode::e_kComma;
        case Qt::Key_Period:
            return ZFUIKeyCode::e_kPeriod;
        case Qt::Key_Slash:
            return ZFUIKeyCode::e_kSlash;

        case Qt::Key_Left:
            return ZFUIKeyCode::e_kLeft;
        case Qt::Key_Up:
            return ZFUIKeyCode::e_kUp;
        case Qt::Key_Right:
            return ZFUIKeyCode::e_kRight;
        case Qt::Key_Down:
            return ZFUIKeyCode::e_kDown;
        case Qt::Key_Home:
            return ZFUIKeyCode::e_kHome;
        case Qt::Key_End:
            return ZFUIKeyCode::e_kEnd;
        case Qt::Key_PageUp:
            return ZFUIKeyCode::e_kPageUp;
        case Qt::Key_PageDown:
            return ZFUIKeyCode::e_kPageDown;
        case Qt::Key_Insert:
            return ZFUIKeyCode::e_kInsert;
        case Qt::Key_Delete:
            return ZFUIKeyCode::e_kDelete;
        case Qt::Key_SysReq:
            return ZFUIKeyCode::e_kPrintScreen;
        case Qt::Key_ScrollLock:
            return ZFUIKeyCode::e_kScrollLock;
        case Qt::Key_Pause:
            return ZFUIKeyCode::e_kPauseBreak;

#if 0
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNum0;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNum1;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNum2;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNum3;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNum4;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNum5;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNum6;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNum7;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNum8;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNum9;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNumLock;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNumAdd;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNumMinus;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNumMultiply;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNumDivide;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNumEnter;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kNumDot;

        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kMediaPlay;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kMediaPause;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kMediaPlayPause;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kMediaStop;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kMediaRecord;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kMediaPrev;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kMediaNext;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kMediaFastForward;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kMediaFastRewind;

        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kVolumeMute;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kVolumeUp;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kVolumeDown;

        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kPhoneCall;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kPhoneCallEnd;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kPhoneHome;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kPhoneMenu;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kPhoneBack;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kPhoneSearch;
        case Qt::Key_unknown:
            return ZFUIKeyCode::e_kPhoneCamera;
#endif
        case Qt::Key_unknown:
        default:
            return ZFUIKeyCode::e_kUnknown;
    }
}

#endif // #if ZF_ENV_sys_Qt

