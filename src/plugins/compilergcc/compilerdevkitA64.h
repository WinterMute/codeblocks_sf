/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef COMPILER_DEVKITA64_H
#define COMPILER_DEVKITA64_H

#include "compiler.h"

class CompilerdevkitA64 : public Compiler
{
    public:
        CompilerdevkitA64();
        virtual ~CompilerdevkitA64();
        virtual AutoDetectResult AutoDetectInstallationDir();
    protected:
        virtual Compiler* CreateCopy();
    private:
};

#endif // COMPILER_DEVKITA64_H
