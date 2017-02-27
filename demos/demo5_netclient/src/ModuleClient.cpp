/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "ModuleClient.h"
#include "base.h"
#include "ModuleMgr.h"
#include "ModuleNetService.h"

using namespace ff::demo;
using namespace ff;

bool ModuleClient::initialize(ModuleMgr& mgr)
{
	/*��ȡ���������ģ��*/
	ff::ModuleNetService* pNetService = mgr.getModule<ff::ModuleNetService>();
	SYS_VERIFY_RV(pNetService != nullptr, false);
	/*����һ���������*/
	mNet = pNetService->getService("testclient");
	SYS_VERIFY_RV(mNet->init(this, 1024), false);
	/*����128�����ӵ�������*/
	for (int32_t i=0; i<128; i++)
	{
		mNet->connect("127.0.0.1", 101011);
	}

	return true;
}

void ModuleClient::finalize()
{
	
}

int64_t ModuleClient::loopTick(int64_t delta)
{
	/*ÿ��ִ�У���һ��������ӷ�������*/
	mNet->send(mIds[rand() % mIds.size()], "hello net");
	return 1000;
}

void ModuleClient::newconn(ff::NetService* net, int32_t id)
{
	SYSLOG_DEBUG("new connection {}.", id);
	mIds.push_back(id);
}

void ModuleClient::lostconn(ff::NetService* net, int32_t id)
{
	SYSLOG_DEBUG("lost connection {}.", id);
	std::remove(mIds.begin(), mIds.end(), id);
}

void ModuleClient::recvdata(ff::NetService* net, int32_t id, const char* data, int32_t datalen)
{

}

