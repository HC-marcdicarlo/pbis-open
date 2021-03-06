/* Editor Settings: expandtabs and use 4 spaces for indentation
 * ex: set softtabstop=4 tabstop=8 expandtab shiftwidth=4: *
 * -*- mode: c, c-basic-offset: 4 -*- */

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

#include "includes.h"

static
LWMsgTypeSpec gSecurityTokenType[] =
{
    LWMSG_ENUM_BEGIN(enum _LW_IO_CREDS_TYPE, 1, LWMSG_UNSIGNED),
    LWMSG_ENUM_VALUE(IO_CREDS_TYPE_PLAIN),
    LWMSG_ENUM_VALUE(IO_CREDS_TYPE_KRB5_CCACHE),
    LWMSG_ENUM_VALUE(IO_CREDS_TYPE_KRB5_TGT),
    LWMSG_ENUM_END,
    LWMSG_TYPE_END
};

LWMsgTypeSpec gSecurityTokenRepSpec[] =
{
    /* Begin structure */
    LWMSG_STRUCT_BEGIN(IO_CREDS),
    /* Discriminator */
    LWMSG_MEMBER_TYPESPEC(IO_CREDS, type, gSecurityTokenType),
    /* Begin union */
    LWMSG_MEMBER_UNION_BEGIN(IO_CREDS, payload),
    /* Union arm -- plain */
    LWMSG_MEMBER_STRUCT_BEGIN(union _LW_IO_CREDS_U, plain),
    LWMSG_MEMBER_PWSTR(struct _LW_IO_CREDS_PLAIN, pwszUsername),
    LWMSG_MEMBER_PWSTR(struct _LW_IO_CREDS_PLAIN, pwszDomain),
    LWMSG_MEMBER_PWSTR(struct _LW_IO_CREDS_PLAIN, pwszPassword),
    LWMSG_ATTR_SENSITIVE,
    LWMSG_STRUCT_END,
    LWMSG_ATTR_TAG(IO_CREDS_TYPE_PLAIN),
    /* Union arm -- krb5 ccache */
    LWMSG_MEMBER_STRUCT_BEGIN(union _LW_IO_CREDS_U, krb5Ccache),
    LWMSG_MEMBER_PWSTR(struct _LW_IO_CREDS_KRB5_CCACHE, pwszPrincipal),
    LWMSG_MEMBER_PWSTR(struct _LW_IO_CREDS_KRB5_CCACHE, pwszCachePath),
    LWMSG_STRUCT_END,
    LWMSG_ATTR_TAG(IO_CREDS_TYPE_KRB5_CCACHE),
    /* Union arm -- krb5 tgt */
    LWMSG_MEMBER_STRUCT_BEGIN(union _LW_IO_CREDS_U, krb5Tgt),
    LWMSG_MEMBER_PWSTR(struct _LW_IO_CREDS_KRB5_TGT, pwszClientPrincipal),
    LWMSG_MEMBER_PWSTR(struct _LW_IO_CREDS_KRB5_TGT, pwszServerPrincipal),
    LWMSG_MEMBER_UINT32(struct _LW_IO_CREDS_KRB5_TGT, authTime),
    LWMSG_MEMBER_UINT32(struct _LW_IO_CREDS_KRB5_TGT, startTime),
    LWMSG_MEMBER_UINT32(struct _LW_IO_CREDS_KRB5_TGT, endTime),
    LWMSG_MEMBER_UINT32(struct _LW_IO_CREDS_KRB5_TGT, renewTillTime),
    LWMSG_MEMBER_UINT32(struct _LW_IO_CREDS_KRB5_TGT, keyType),
    LWMSG_MEMBER_UINT32(struct _LW_IO_CREDS_KRB5_TGT, ulKeySize),
    LWMSG_MEMBER_POINTER(struct _LW_IO_CREDS_KRB5_TGT, pKeyData, LWMSG_UINT8(BYTE)),
    LWMSG_ATTR_SENSITIVE,
    LWMSG_ATTR_LENGTH_MEMBER(struct _LW_IO_CREDS_KRB5_TGT, ulKeySize),
    LWMSG_MEMBER_UINT32(struct _LW_IO_CREDS_KRB5_TGT, tgtFlags),
    LWMSG_MEMBER_UINT32(struct _LW_IO_CREDS_KRB5_TGT, ulTgtSize),
    LWMSG_MEMBER_POINTER(struct _LW_IO_CREDS_KRB5_TGT, pTgtData, LWMSG_UINT8(BYTE)),
    LWMSG_ATTR_SENSITIVE,
    LWMSG_ATTR_LENGTH_MEMBER(struct _LW_IO_CREDS_KRB5_TGT, ulTgtSize),
    LWMSG_STRUCT_END,
    LWMSG_ATTR_TAG(IO_CREDS_TYPE_KRB5_TGT),
    /* End union */
    LWMSG_UNION_END,
    LWMSG_ATTR_DISCRIM(IO_CREDS, type),
    /* End structure */
    LWMSG_STRUCT_END,
    LWMSG_TYPE_END
};

static LWMsgTypeSpec gStatusReplySpec[] =
{
    /* Begin structure */
    LWMSG_STRUCT_BEGIN(LWIO_STATUS_REPLY),
    /* err - marshal as 32-bit unsigned integer */
    LWMSG_MEMBER_UINT32(LWIO_STATUS_REPLY, dwError),
    /* End structure */
    LWMSG_STRUCT_END,
    LWMSG_TYPE_END
};

static LWMsgTypeSpec gDriverNameSpec[] =
{
    LWMSG_PWSTR,
    LWMSG_ATTR_NOT_NULL,
    LWMSG_TYPE_END
};

static LWMsgTypeSpec gDriverStateSpec[] =
{
    LWMSG_UINT8(LWIO_DRIVER_STATE),
    LWMSG_ATTR_RANGE(LWIO_DRIVER_STATE_UNKNOWN, LWIO_DRIVER_STATE_LOADED),
    LWMSG_TYPE_END
};

static LWMsgTypeSpec gPidSpec[] =
{
    LWMSG_INT32(pid_t),
    LWMSG_TYPE_END
};

static LWMsgProtocolSpec gLwIoDaemonProtocolSpec[] =
{
    LWMSG_MESSAGE(LWIO_QUERY_STATE_DRIVER,          gDriverNameSpec),
    LWMSG_MESSAGE(LWIO_QUERY_STATE_DRIVER_SUCCESS,  gDriverStateSpec),
    LWMSG_MESSAGE(LWIO_QUERY_STATE_DRIVER_FAILED,   gStatusReplySpec),
    LWMSG_MESSAGE(LWIO_LOAD_DRIVER,                 gDriverNameSpec),
    LWMSG_MESSAGE(LWIO_LOAD_DRIVER_SUCCESS,         gStatusReplySpec),
    LWMSG_MESSAGE(LWIO_LOAD_DRIVER_FAILED,          gStatusReplySpec),
    LWMSG_MESSAGE(LWIO_UNLOAD_DRIVER,               gDriverNameSpec),
    LWMSG_MESSAGE(LWIO_UNLOAD_DRIVER_SUCCESS,       gStatusReplySpec),
    LWMSG_MESSAGE(LWIO_UNLOAD_DRIVER_FAILED,        gStatusReplySpec),
    LWMSG_MESSAGE(LWIO_GET_PID,                     NULL),
    LWMSG_MESSAGE(LWIO_GET_PID_SUCCESS,             gPidSpec),
    LWMSG_MESSAGE(LWIO_GET_PID_FAILED,              gStatusReplySpec),
    LWMSG_PROTOCOL_END
};

NTSTATUS
LwIoDaemonIpcAddProtocolSpec(
    IN OUT LWMsgProtocol* pProtocol
    )
{
    NTSTATUS status = 0;
    int EE = 0;
    LWMsgStatus msgStatus = 0;

    msgStatus = lwmsg_protocol_add_protocol_spec(pProtocol, gLwIoDaemonProtocolSpec);
    status = NtIpcLWMsgStatusToNtStatus(msgStatus);
    GOTO_CLEANUP_ON_STATUS_EE(status, EE);

cleanup:

    LOG_LEAVE_IF_STATUS_EE(status, EE);

    return status;
}
