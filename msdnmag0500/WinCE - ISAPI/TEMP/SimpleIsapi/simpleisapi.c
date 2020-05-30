#define IN
#define OUT

#include <windows.h>
#include <httpext.h>


void PrintVar (IN EXTENSION_CONTROL_BLOCK *, IN CHAR *); 


/****************************************************************************
*
*   FUNCTION: GetExtensionVersion
*   
*   PURPOSE:  Standart procedure which needs to be exported from the DLL.
*   
*   PARAMETRS: 
*             pVer - pointer to version information structure.
*
*   RETURN:   BOOL
*
*   COMMENTS: Will be called by the server.
*
****************************************************************************/

BOOL WINAPI GetExtensionVersion (HSE_VERSION_INFO *pVer)
{
    pVer->dwExtensionVersion = MAKELONG(HSE_VERSION_MINOR, HSE_VERSION_MAJOR);
    strcpy(pVer->lpszExtensionDesc,"HTTP Dump Application");
    return TRUE;
} // GetExtensionVersion()



/****************************************************************************
*
*   FUNCTION: HttpExtensionProc
*   
*   PURPOSE:  Standart procedure which needs to be exported from the DLL.
*   
*   PARAMETRS: 
*             pECB - pointer to version extension control block.
*
*   RETURN:   DWORD, status code.
*
*   COMMENTS: Will be called by the server.
*
****************************************************************************/

DWORD WINAPI HttpExtensionProc (EXTENSION_CONTROL_BLOCK *pECB)
{
    CHAR *Vars[]	=
    {
    	"AUTH_TYPE",
    	"CONTENT_LENGTH",	
    	"CONTENT_TYPE",	
    	"PATH_INFO",
        "PATH_TRANSLATED",
    	"GATEWAY_INTERFACE",
    	"QUERY_STRING",	
    	"REMOTE_ADDR",	
    	"REMOTE_HOST",	
    	"REMOTE_USER",	
    	"UNMAPPED_REMOTE_USER",
    	"REQUEST_METHOD",	
    	"SCRIPT_NAME", 
    	"SERVER_NAME",
    	"SERVER_PORT",
    	"SERVER_PORT_SECURE",
    	"SERVER_PROTOCOL",
    	"SERVER_SOFTWARE",
    	"HTTP_ACCEPT",
    	"URL",
    	"ALL_HTTP",
    };
    CHAR  szBuff[4096], *lpszTemp = NULL;
	DWORD dwLen = sizeof (szBuff), cbQuery, dwBytesRemaining;
	int i;

	sprintf ( szBuff, "Content-Type: text/plain\r\n\r\n");

    dwLen = strlen ( szBuff );
    pECB -> ServerSupportFunction ( pECB -> ConnID,
    		                        HSE_REQ_SEND_RESPONSE_HEADER, 
                                    "200 OK",
                                    &dwLen, 
                                    (LPDWORD) szBuff );


	if ( !strcmp ( pECB -> lpszMethod, "GET") )
	{
		sprintf  ( szBuff, "<h3>See QUERY_STRING variable "
                            "for incoming data.</h3><hr>\r\n");
		dwLen = strlen ( szBuff );
		pECB -> WriteClient (pECB -> ConnID, szBuff, &dwLen, 0);
	}
	else
	{
        // POST
        if ( pECB -> cbTotalBytes == 0)     			  
		{
            // No Query at all
			sprintf ( szBuff, "<h3>No incoming data</h3><br>\r\n" );
	        dwLen = strlen ( szBuff );
		    pECB -> WriteClient ( pECB -> ConnID, szBuff, &dwLen, 0 );
		    return HSE_STATUS_ERROR;
		}
        else
        {
            // Start processing of input information here.
            if( ! ( lpszTemp = ( CHAR * ) LocalAlloc ( LPTR, 
                                          pECB -> cbTotalBytes ) ) )	
                return HSE_STATUS_ERROR;
            strcpy ( lpszTemp,  ( CHAR * ) pECB -> lpbData );
            
            dwBytesRemaining=pECB->cbTotalBytes - pECB->cbAvailable;
            while (dwBytesRemaining > 0 )
            {            
                pECB -> ReadClient ( pECB -> ConnID,  ( LPVOID ) 
                              ( lpszTemp + pECB->cbAvailable ), &cbQuery );
                dwBytesRemaining -= cbQuery;
			}
            
            
			sprintf  ( szBuff, "<h3>Incoming data:</h3><br>\r\n");
			dwLen = strlen ( szBuff );
			pECB -> WriteClient (pECB -> ConnID, szBuff, &dwLen, 0);

		    if (lpszTemp != NULL ) 
			{
				// if not empty string.
				dwLen = strlen (lpszTemp);
				pECB -> WriteClient ( pECB -> ConnID, lpszTemp, &dwLen, 0 );
			}

			sprintf  ( szBuff, "<hr>\r\n");
			dwLen = strlen ( szBuff );
			pECB -> WriteClient (pECB -> ConnID, szBuff, &dwLen, 0);		
        }

	}

	sprintf  ( szBuff, "<TABLE BORDER=1><CAPTION><h3>HTTP Variables"
			                "</h3></CAPTION>");
	dwLen = strlen ( szBuff );
	pECB -> WriteClient (pECB -> ConnID, szBuff, &dwLen, 0);

    // Get and print each server variable in the array.
	for (i=0; i <= 20; i++)
		PrintVar (pECB, Vars[i]);

    // Create HTML table footer.    
	sprintf  ( szBuff, "</TABLE>");
	dwLen = strlen ( szBuff );
	pECB -> WriteClient (pECB -> ConnID, szBuff, &dwLen, 0);
	LocalFree (lpszTemp);
	return HSE_STATUS_SUCCESS;
}


/****************************************************************************
*   
*   FUNCTION: PrintVar
*
*   PURPOSE: Gets the value for the server variable and outputs it in the 
*            table cell.
*   
*   PARAMETRS: 
*           pECB - pointer to extension control block,
*           pszVar - pointer to the server variable.
*
*   RETURN:   none
*          
****************************************************************************/

void PrintVar (EXTENSION_CONTROL_BLOCK *pECB, CHAR *pszCurVar)
{
    CHAR   szBuff[4096], *lpszOut = NULL, szMsg[] = "No such variable";
	DWORD dwLen = 0, dwError, dwSize;

	if ( !pECB -> GetServerVariable (pECB -> ConnID,   // Connection id
                                     pszCurVar,        // Variable  
                                     NULL,             // Buffer 
                                     &dwLen))          // Length
	{	
        // This call shoudl always fail with ERROR_INSUFFICIENT_BUFFER,
        // since we supplied NULL buffer. As a result, dwLen will
        // indicate the size of the buffer to allocate	
		if ( ( ( dwError= GetLastError ()) != ERROR_INSUFFICIENT_BUFFER ) 
             && ( dwError != ERROR_INVALID_INDEX ) )
		{
			sprintf  ( szBuff, "GetServerVariable error: %d ", dwError);
			dwLen = strlen ( szBuff );
			pECB -> WriteClient (pECB -> ConnID, szBuff, &dwLen, 0);
			return;
		}
	}
  
	if ( dwError == ERROR_INVALID_INDEX)
    {
	    lpszOut = szMsg;
        dwLen = sizeof (szMsg);
    }
	else
	{
        lpszOut = (CHAR *) LocalAlloc (LPTR, dwLen);
		// Variable exists
		if ( !pECB -> GetServerVariable (pECB -> ConnID,
                                         pszCurVar, 
                                         lpszOut, 
                                         &dwLen))
		{						 
			sprintf ( szBuff, "GetServerVariable error: %d", GetLastError());
			dwLen = strlen ( szBuff );
			pECB -> WriteClient (pECB -> ConnID, szBuff, &dwLen, 0);
			return;
		}

	}
	sprintf (szBuff, "<TR><TD WIDTH=258> %s "
			              "</TD><TD WIDTH=258>", pszCurVar);
    dwSize = strlen ( szBuff );
	pECB -> WriteClient (pECB -> ConnID, szBuff, &dwSize, 0);

	if ( strlen (lpszOut) != 0)
	{
		dwLen--; // Get rid of the last NULL
		pECB -> WriteClient (pECB -> ConnID, lpszOut, &dwLen, 0);
	}
	else
	{
		// Variable is empty
		sprintf (szBuff, "Variable has empty value");
		dwLen = strlen ( szBuff ) ;
		pECB -> WriteClient (pECB -> ConnID, szBuff, &dwLen, 0);
	}

 	sprintf (szBuff, "</TD></TR>\r\n");
	dwLen = strlen ( szBuff );
	pECB -> WriteClient (pECB -> ConnID, szBuff, &dwLen, 0);

	if (lpszOut != szMsg)
        // In this case lpszOut was allocated dynamicly.
    	LocalFree (lpszOut);
	return;

}

