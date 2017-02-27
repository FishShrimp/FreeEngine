/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include <cinttypes>
#include <string>
#include <functional>

#include "base.h"
#include "ModuleMgr.h"
#include "Framework.h"
#include "ModuleMgr.h"
#include "Config.h"

#include "ModuleTest.h"
#include "ModuleLuaMachine.h"
#include "ModuleLuaExport.h"

namespace ff
{
	namespace demo
	{
		class ServerFramework : public ff::Framework
		{
		private:


		protected:
			virtual bool initialize()
			{
				// ��ע������ģ��
				SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleTest>(), false);
				SYS_VERIFY_RV(mModuleMgr.registerModule<ff::ModuleLuaMachine>(), false);
				SYS_VERIFY_RV(mModuleMgr.registerModule<ff::ModuleLuaExport>(), false);

				return true;
			}

			virtual void finalize()
			{

			}
		};

		static ServerFramework app;
	}
}
