/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFUIKit_test.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZF_GLOBAL_INITIALIZER_INIT(ZFUIOnScreenKeyboardState_test)
{
    this->listener = ZFCallbackForRawFunction(zfself::keyboardStateOnChange);
    ZFUIOnScreenKeyboardState::instanceForSysWindow()->observerAdd(ZFUIOnScreenKeyboardState::EventKeyboardStateOnChange(), this->listener);
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFUIOnScreenKeyboardState_test)
{
    ZFUIOnScreenKeyboardState::instanceForSysWindow()->observerRemove(ZFUIOnScreenKeyboardState::EventKeyboardStateOnChange(), this->listener);
}
private:
    ZFListener listener;
    static ZFLISTENER_PROTOTYPE_EXPAND(keyboardStateOnChange)
    {
        zfLogTrimT() << zfText("[ZFUIOnScreenKeyboardState]") << listenerData.sender;
    }
ZF_GLOBAL_INITIALIZER_END(ZFUIOnScreenKeyboardState_test)

ZF_NAMESPACE_GLOBAL_END

