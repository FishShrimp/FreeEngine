

#include <fstream>
#include "Reloadable.h"
#include "ut_file.h"

namespace ff {

	Reloadable::Reloadable(std::string fname)
	{
		mFileName = fname;
		mWriteTime = 0;
	}

	bool Reloadable::tryReload()
	{
		// �Ӳ��ļ��޸�ʱ�䣬�޸�ʱ��仯ʱ�Ž������滻
		int64_t nCurWriteTime = ut_file_modifytime(mFileName.c_str());
		if (nCurWriteTime == mWriteTime)
		{
			return false;
		}

		// ���Դ��ļ��������ʧ�����ܽ����ȼ���
		std::ifstream ifile(mFileName, std::ios::binary);
		if (!ifile.good()) {
			return false;
		}
		ifile.close();

		// ���ؽ��ڴ棬׼���������滻
		if (!doReload())
		{
			return false;
		}

		mWriteTime = nCurWriteTime;
		return true;
	}
}