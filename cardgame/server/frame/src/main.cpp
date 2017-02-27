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
#include "CfgIni.h"

#include "ModuleHotSwap.h"
#include "ModuleNetService.h"
#include "ModuleRocksDb.h"
#include "ModuleNetMsgTrigger.h"
#include "ModuleLogin.h"
#include "ModuleDataSync.h"

namespace ff
{
	class ServerFramework : public Framework
	{
	private:


	protected:
		virtual bool initialize()
		{
#ifdef UT_PLATFORM_WINDOWS
			if (!CfgIni::instance().load("servcfg.ini"))
#else
			if (!CfgIni::instance().load("servcfg_linux.ini"))
#endif
			{
				SYSLOG_ERROR("load config file servcfg.ini failed.");
				return false;
			}

			// ��ע������ģ��

			// ����ģ��
			SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleNetService>(), false);
			// �ȸ��߼�ģ��
			SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleHotSwap>(), false);
			// ��½����ģ��
			SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleLogin>(), false);
			SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleNetMsgTrigger>(), false);
			SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleDataSync>(), false);
			SYS_VERIFY_RV(mModuleMgr.registerModule<ModuleRocksDb>(), false);			

			return true;
		}

		virtual void finalize()
		{
			
		}
	};

	static ServerFramework app;
}

