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
#include "compilerdevkitPPC.h"
#include "manager.h"
#include "macrosmanager.h"
#include "logmanager.h"
#include <configmanager.h>

#ifdef __WXMSW__
    #include <wx/dir.h>
    #include <wx/msw/registry.h>
#endif

CompilerdevkitPPC::CompilerdevkitPPC()
    : Compiler(_("devkitPPC"), _T("devkitppc-gcc"))
{
    m_Weight = 8;
    Reset();
}

CompilerdevkitPPC::~CompilerdevkitPPC()
{
    //dtor
}

Compiler * CompilerdevkitPPC::CreateCopy()
{
    return (new CompilerdevkitPPC(*this));
}

AutoDetectResult CompilerdevkitPPC::AutoDetectInstallationDir()
{
    wxString sep = wxFileName::GetPathSeparator();
    // look first if devkitPPC was installed with Code::Blocks
    wxString testPath = ConfigManager::GetExecutableFolder();
    if (!wxFileExists(testPath + sep + _T("devkitPPC") + sep + _T("bin") + sep + m_Programs.C))
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

    m_MasterPath = testPath + sep + _T("devkitPPC");
    AutoDetectResult ret = wxFileExists(m_MasterPath + sep + _T("bin") + sep + m_Programs.C) ? adrDetected : adrGuessed;
    if (ret == adrDetected)
    {
        AddIncludeDir(testPath + sep + _T("devkitPPC") + sep + _T("powerpc-eabi") + sep + _T("include"));
        if (platform::windows)
            if (wxFileExists(testPath + sep + _T("msys") + sep + _T("bin") + sep + m_Programs.MAKE))
                m_ExtraPaths.Add(testPath + sep + _T("msys") + sep + _T("bin"));
    }

    return ret;
} // end of AutoDetectInstallationDir
