#import "dpsops.h"
/* /Net/beseler/BinCache3/AppKit/Symbols/AppKit-120.sym~3/derived_src/DPSClient.subproj/ContextWraps.subproj/DPSopenstep.h generated from /Net/beseler/BinCache3/AppKit/Symbols/AppKit-120.sym~3/derived_src/DPSClient.subproj/ContextWraps.subproj/DPSopenstep.psw
   by unix pswrap V1.009  Wed Apr 19 17:50:24 PDT 1989
 */

#ifndef DPSOPENSTEP_H
#define DPSOPENSTEP_H
#include "AppKitDefines.h"

APPKIT_EXTERN void DPScomposite(DPSContext ctxt, float x, float y, float w, float h, int gstateNum, float dx, float dy, int op);

APPKIT_EXTERN void DPScompositerect(DPSContext ctxt, float x, float y, float w, float h, int op);

APPKIT_EXTERN void DPSdissolve(DPSContext ctxt, float x, float y, float w, float h, int gstateNum, float dx, float dy, float delta);

APPKIT_EXTERN void DPSsetalpha(DPSContext ctxt, float a);

APPKIT_EXTERN void DPScurrentalpha(DPSContext ctxt, float *alpha);

#endif DPSOPENSTEP_H
