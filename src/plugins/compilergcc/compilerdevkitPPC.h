/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef COMPILER_DEVKITPPC_H
#define COMPILER_DEVKITPPC_H

#include "compiler.h"

class CompilerdevkitPPC : public Compiler
{
    public:
        CompilerdevkitPPC();
        virtual ~CompilerdevkitPPC();
        virtual AutoDetectResult AutoDetectInstallationDir();
    protected:
        virtual Compiler* CreateCopy();
    private:
};

#endif // COMPILER_DEVKITPPC_H
