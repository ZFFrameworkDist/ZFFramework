#include "ZFUIViewCapture.h"
#include "protocol/ZFProtocolZFUIViewCapture.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_FUNC_DEFINE_1(zfautoObjectT<ZFUIImage *>, ZFUIViewCapture,
                       ZFMP_IN(ZFUIView *, view))
{
    if(view == zfnull)
    {
        return zfnull;
    }
    zfautoObjectT<ZFUIImage *> ret = ZFUIImage::ClassData()->newInstance();
    if(!ZFPROTOCOL_ACCESS(ZFUIViewCapture)->viewCapture(view, ret.to<ZFUIImage *>()))
    {
        return zfnull;
    }
    return ret;
}

ZF_NAMESPACE_GLOBAL_END

