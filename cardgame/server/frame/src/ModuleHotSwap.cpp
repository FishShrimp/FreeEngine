

#include <memory>

#include "CfgIni.h"
#include "StringUtil.h"
#include "ModuleHotSwap.h"
#include "base.h"
#include "ValueOpt.h"
#include "cfg_loader.h"
#include "ReloadMgr.h"
#include "ReloadCfg.h"
#include "ReloadLogicPlugin.h"
#include "HotSwapPluginProxy.h"

using namespace ff;

bool ModuleHotSwap::initialize(ff::ModuleMgr& mgr)
{
	std::string cfgFile = CfgIni::instance().get<std::string>("data", "file");
	std::string logicFile = CfgIni::instance().get<std::string>("hslogic", "file");
	// �߻����õ��ȸ�
	ReloadMgr::instance().addReloadable(std::shared_ptr<ReloadCfg>(new ReloadCfg(cfgFile)));
	// ��Ϸ�߼����ȸ�
	ReloadMgr::instance().addReloadable(std::shared_ptr<ReloadLogicPlugin>(new ReloadLogicPlugin(logicFile)));
	// �״�����ʱ����������һ��
	ReloadMgr::instance().makeReload();
	ReloadMgr::instance().confirmReload();

	// �Ӳ�һ���߼�ģ���Ƿ�׼������
	SYS_VERIFY_RV(HotSwapPluginProxy::instance().good(), false);

	return true;
}

void ModuleHotSwap::finalize()
{

}

int32_t ModuleHotSwap::runOnce()
{
	ReloadMgr::instance().makeReload();

	return 1000;
}

int64_t ModuleHotSwap::loopTick(int64_t delta)
{
	ReloadMgr::instance().confirmReload();

	return 1000;
}

