/* Editor Settings: expandtabs and use 4 spaces for indentation
 * ex: set softtabstop=4 tabstop=8 expandtab shiftwidth=4: *
 */

/*
 * Copyright © BeyondTrust Software 2004 - 2019
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * BEYONDTRUST MAKES THIS SOFTWARE AVAILABLE UNDER OTHER LICENSING TERMS AS
 * WELL. IF YOU HAVE ENTERED INTO A SEPARATE LICENSE AGREEMENT WITH
 * BEYONDTRUST, THEN YOU MAY ELECT TO USE THE SOFTWARE UNDER THE TERMS OF THAT
 * SOFTWARE LICENSE AGREEMENT INSTEAD OF THE TERMS OF THE APACHE LICENSE,
 * NOTWITHSTANDING THE ABOVE NOTICE.  IF YOU HAVE QUESTIONS, OR WISH TO REQUEST
 * A COPY OF THE ALTERNATE LICENSING TERMS OFFERED BY BEYONDTRUST, PLEASE CONTACT
 * BEYONDTRUST AT beyondtrust.com/contact
 */

/*
 * Copyright (C) BeyondTrust Software. All rights reserved.
 *
 * Module Name:
 *
 *        netr_credentials.h
 *
 * Abstract:
 *
 *        Remote Procedure Call (RPC) Client Interface
 *
 *        Netlogon credentials functions (rpc client library)
 *
 * Authors: Rafal Szczesniak (rafal@likewise.com)
 */

#ifndef _NETR_CREDENTIALS_H_
#define _NETR_CREDENTIALS_H_


#define GETUINT8(buf, off)                      \
    ((UINT8)(buf)[(off)])

#define GETUINT16(buf, off)                     \
    (((UINT16)GETUINT8((buf), 0+(off))) |       \
     ((UINT16)GETUINT8((buf), 1+(off)) << 8))

#define GETUINT32(buf, off)                     \
    (((UINT32)GETUINT16((buf), 0+(off))) |      \
     ((UINT32)GETUINT16((buf), 2+(off)) << 16))

#define SETUINT8(buf, off, v)                   \
    ((buf)[(off)] = (UINT8)((v) & 0xff))

#define SETUINT16(buf, off, v)                  \
    do {                                        \
        SETUINT8((buf), 0+(off), (v));          \
        SETUINT8((buf), 1+(off), ((v) >> 8));   \
    } while (0)

#define SETUINT32(buf, off, v)                  \
    do {                                        \
        SETUINT16((buf), 0+(off), (v));         \
        SETUINT16((buf), 2+(off), ((v) >> 16)); \
    } while (0)


VOID
NetrCredentialsCliStep(
    IN OUT NetrCredentials *pCreds
    );


VOID
NetrCredentialsSrvStep(
    IN OUT NetrCredentials *pCreds
    );


VOID
NetrGetNtHash(
    OUT BYTE    Hash[16],
    IN  PCWSTR  pwszPassword
    );


VOID
NetrGetLmHash(
    OUT BYTE    Hash[16],
    IN  PCWSTR  pwszPassword
    );


#endif /* _NETR_CREDENTIALS_H_ */


/*
local variables:
mode: c
c-basic-offset: 4
indent-tabs-mode: nil
tab-width: 4
end:
*/
