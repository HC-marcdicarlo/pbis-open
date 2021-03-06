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

/*
 * Copyright (C) BeyondTrust Software. All rights reserved.
 *
 * Module Name:
 *
 *        main.c
 *
 * Abstract:
 *
 *        BeyondTrust Task Service (LWTASK)
 *
 *        Share Migration Test Driver
 *
 * Authors: Sriram Nambakam (snambakam@likewise.com)
 *
 */

#include <config.h>
#include <lwtasksystem.h>

#include <lwdef.h>
#include <lwerror.h>

#include <lwtaskdef.h>
#include <lwtaskutils.h>
#include <lwtasklog_r.h>

#include <lwmigrate.h>

static
VOID
ShowUsage(
    VOID
    );

int
main(
    int   argc,
    char* argv[]
    )
{
    DWORD dwError = 0;
    BOOLEAN bShutdown = FALSE;
    PLW_SHARE_MIGRATION_CONTEXT pContext = NULL;

    if (argc == 2 && (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")))
    {
        ShowUsage();
        goto cleanup;
    }

    if (argc < 5)
    {
        dwError = ERROR_BAD_ARGUMENTS;
        BAIL_ON_LW_TASK_ERROR(dwError);
    }

    dwError = LwTaskMigrateInit();
    BAIL_ON_LW_TASK_ERROR(dwError);

    bShutdown = TRUE;

    dwError = LwTaskMigrateCreateContext(
                    argv[3], /* User name   */
                    argv[4], /* Password    */
                    &pContext);
    BAIL_ON_LW_TASK_ERROR(dwError);

    dwError = LwTaskMigrateShareA(
                    pContext,
                    argv[1], /* Server name */
                    argv[2], /* Share name  */
                    0        /* Flags       */
                    );
    BAIL_ON_LW_TASK_ERROR(dwError);

cleanup:

    if (pContext)
    {
        LwTaskMigrateCloseContext(pContext);
    }

    if (bShutdown)
    {
        LwTaskMigrateShutdown();
    }

    return dwError;

error:

    switch (dwError)
    {
        case ERROR_BAD_ARGUMENTS:

            ShowUsage();

            break;

        default:

            fprintf(stderr, "Error migrating share. Code %u\n", dwError);

            break;
    }

    goto cleanup;
}

static
VOID
ShowUsage(
    VOID
    )
{
    fprintf(stderr,
            "Usage: lwmigrate <server> <share> <user> <password>\n");
}
