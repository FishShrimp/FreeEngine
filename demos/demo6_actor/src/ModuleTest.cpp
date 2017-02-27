/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#include <functional>

#include "ModuleTest.h"
#include "base.h"

#include "ModuleMgr.h"
#include "ModuleActor.h"
#include "ActorNormalWorker.h"

using namespace ff::demo;
using namespace ff;

bool ModuleTest::initialize(ModuleMgr& mgr)
{
	ff::ModuleActor* pActor = mgr.getModule<ff::ModuleActor>();
	SYS_VERIFY_RV(pActor != nullptr, false);
	/*ע��4����ͨ��������*/
	for (int32_t i=0; i<4; i++)
	{
		pActor->registerActor("normal", new ff::ActorNormalWorker());
	}

	/*���8����ʱ������*/
	for (int32_t i=0; i<8; i++)
	{
		ff::ActorNormalWorker::Work* work = new ff::ActorNormalWorker::Work(std::bind(&ModuleTest::hardwork, this));
		work->setCallback(std::bind(&ModuleTest::workfinish, this, std::placeholders::_1), 10000);
		pActor->dispatchWork("normal", work);
	}

	return true;
}

void ModuleTest::finalize()
{
	
}

void ModuleTest::hardwork()
{
	SYSLOG_DEBUG("work start in actor thread.");
	// �ܺ�ʱ�Ĳ���,�����actor�߳��в���
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void ModuleTest::workfinish(ff::ActorWork* work)
{
	// ֪ͨ������ɣ�����������̵߳���
	SYSLOG_DEBUG("work finished in main thread.");
}