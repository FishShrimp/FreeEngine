/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#include "ModuleTest.h"
#include "base.h"

#include "ModuleMgr.h"
#include "ModuleLuaMachine.h"
#include "LuaExportFuncs.h"

using namespace ff::demo;
using namespace ff;

bool ModuleTest::initialize(ModuleMgr& mgr)
{
	// ע��2��������lua��
	LuaExportFuncs::instance().registerFunc("test.func1", this, &ModuleTest::testFunc1);
	LuaExportFuncs::instance().registerFunc("test.func2", this, &ModuleTest::testFunc2);

	ModuleLuaMachine* pLuaMachine = mgr.getModule<ModuleLuaMachine>();
	SYS_VERIFY_RV(pLuaMachine != nullptr, false);
	// ������ڽű��ļ�
	pLuaMachine->initLuaMachine("script/test.lua");

	return true;
}

void ModuleTest::finalize()
{
	
}

void ModuleTest::preStartLoop()
{
	
}

int32_t ModuleTest::testFunc1(int32_t a, int32_t b)
{
	return a + b;
}

std::string ModuleTest::testFunc2(std::string a, std::string b)
{
	return a + b;
}