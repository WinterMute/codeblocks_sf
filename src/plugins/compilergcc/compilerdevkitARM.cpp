/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 * $Revision$
 * $Id$
 * $HeadURL$
 */

#include <sdk.h>
#include <prep.h>
#ifndef CB_PRECOMP
    #include <wx/intl.h>
    #include <wx/regex.h>
    #include <wx/utils.h> // wxGetOSDirectory, wxGetEnv
#endif
#include <wx/filefn.h> // wxFileExists
#include <wx/fileconf.h> // wxFileConfig
#include "compilerdevkitARM.h"
#include "manager.h"
#include "macrosmanager.h"
#include "logmanager.h"
#include <configmanager.h>

#ifdef __WXMSW__
    #include <wx/dir.h>
    #include <wx/msw/registry.h>
#endif

CompilerdevkitARM::CompilerdevkitARM()
    : Compiler(_("devkitARM"), _T("devkitarm-gcc"))
{
    m_Weight = 8;
    Reset();
}

CompilerdevkitARM::~CompilerdevkitARM()
{
    //dtor
}

Compiler * CompilerdevkitARM::CreateCopy()
{
    return (new CompilerdevkitARM(*this));
}

AutoDetectResult CompilerdevkitARM::AutoDetectInstallationDir()
{
    wxString sep = wxFileName::GetPathSeparator();
    // look first if devkitARM was installed with Code::Blocks
    wxString testPath = ConfigManager::GetExecutableFolder();
    if (!wxFileExists(testPath + sep + _T("devkitARM") + sep + _T("bin") + sep + m_Programs.C))
    {
        testPath.Truncate(0);
#ifdef __WXMSW__ // for wxRegKey
        wxRegKey key( _T("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\devkitProUpdater") );

        if (key.Exists()) key.QueryValue(_T("InstallLocation"), testPath);
#endif // __WXMSW__
        if (!platform::windows)
        {
            testPath = wxGetenv(_T("DEVKITPRO"));
        }
    }

    if (testPath.IsEmpty())
    {
        if (platform::windows)
        {
            testPath = _T("C:/devkitPro");
        }
        else
        {
            testPath = _T("/opt/devkitpro");
        }
    }

    m_MasterPath = testPath + sep + _T("devkitARM");
    AutoDetectResult ret = wxFileExists(m_MasterPath + sep + _T("bin") + sep + m_Programs.C) ? adrDetected : adrGuessed;
    if (ret == adrDetected)
    {
        AddIncludeDir(testPath + sep + _T("devkitARM") + sep + _T("arm-none-eabi") + sep + _T("include"));
        if (platform::windows)
            if (wxFileExists(testPath + sep + _T("msys") + sep + _T("bin") + sep + m_Programs.MAKE))
                m_ExtraPaths.Add(testPath + sep + _T("msys") + sep + _T("bin"));
    }

    return ret;
} // end of AutoDetectInstallationDir
