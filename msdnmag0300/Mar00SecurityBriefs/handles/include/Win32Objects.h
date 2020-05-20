#pragma once

struct Win32Object
{
    enum ObjectTypes {
        otProcess = 1,  __otFirst = otProcess,
        otThread,
        otMutex,
        otSemaphore,
        otEvent,
        otSection,
        otJob,
        otTimer,
        otToken,
        otFile,
        otNamedPipe,
        otRegistryKey,
        otWinSta,       __otLast = otNamedPipe      
    };

    static Win32Object* Create( ObjectTypes ot );

    Win32Object( DWORD grfMax,
                 SE_OBJECT_TYPE objType,
                 bool bCanBeNamed,
                 bool bCanExpandHandlePermissions,
                 const wchar_t* pszObjTypeName )
      : m_grfMax( grfMax ),
        m_objType( objType ),
        m_bCanBeNamed( bCanBeNamed ),
        m_bCanExpandHandlePermissions( bCanExpandHandlePermissions ),
        m_pszObjTypeName( pszObjTypeName )
    {}

    DWORD           GetMaxAccessMask() { return m_grfMax; }
    SE_OBJECT_TYPE  GetObjectType() { return m_objType; }
    bool            CanBeNamed()    { return m_bCanBeNamed; }
    bool            CanExpandHandlePermissions() { return m_bCanExpandHandlePermissions; }
    const wchar_t*  GetObjectTypeName() { return m_pszObjTypeName; }
    virtual HANDLE  CreateObject( bool bInherit, const wchar_t* pszSuggestedName = 0, wchar_t* pszActualName = 0 ) = 0;
    virtual HANDLE  OpenObject( const wchar_t* psz, DWORD grfAccess ) { return 0; }
    virtual void    CloseObject( HANDLE h, const wchar_t* ) { CloseHandle(h); }
    virtual bool    UseObject( HANDLE h ) = 0;

    // base class implementation maps standard/generic permissions
    virtual const wchar_t* MapPermissionName( DWORD nPermission );
    void MapPermissionNames( DWORD grfAccess, wchar_t* pszResult, const wchar_t* pszDelim = L" | " );

    const DWORD             m_grfMax;
    const SE_OBJECT_TYPE    m_objType;
    const bool              m_bCanBeNamed;
    const bool              m_bCanExpandHandlePermissions;
    const wchar_t* const    m_pszObjTypeName;
};
