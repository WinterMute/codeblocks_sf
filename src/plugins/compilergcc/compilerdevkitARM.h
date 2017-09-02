/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef COMPILER_DEVKITARM_H
#define COMPILER_DEVKITARM_H

#include "compiler.h"

class CompilerdevkitARM : public Compiler
{
    public:
        CompilerdevkitARM();
        virtual ~CompilerdevkitARM();
        virtual AutoDetectResult AutoDetectInstallationDir();
    protected:
        virtual Compiler* CreateCopy();
    private:
};

#endif // COMPILER_DEVKITARM_H
