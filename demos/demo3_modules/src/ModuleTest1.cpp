/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "ModuleTest1.h"
#include "ModuleMgr.h"
#include "base.h"


using namespace ff::demo;
using namespace ff;

bool ModuleTest1::initialize(ModuleMgr& mgr)
{
	mModuleTest2 = mgr.getModule<ModuleTest2>();
	SYSLOG_DEBUG("ModuleTest initialize.");
	return true;
}

void ModuleTest1::finalize()
{
	SYSLOG_DEBUG("ModuleTest finalize.");
}

void ModuleTest1::hello()
{
	SYSLOG_DEBUG("ModuleTest1 hello.");
	/*����ģ��2�ĺ���hello*/
	mModuleTest2->hello();
}

int64_t ModuleTest1::loopTick(int64_t delta)
{
	this->hello();
	return 3000;
}