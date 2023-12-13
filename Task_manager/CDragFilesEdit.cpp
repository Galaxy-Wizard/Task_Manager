#include "pch.h"

#include "CDragFilesEdit.h"
BEGIN_MESSAGE_MAP(CDragFilesEdit, CEdit)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


void CDragFilesEdit::OnDropFiles(HDROP hDropInfo)
{
	const UINT path_length = 10000;
	UINT count;
	WCHAR *file_path = new WCHAR[path_length];

	if (file_path != nullptr)
	{
		count = DragQueryFileW(hDropInfo, -1, NULL, 0);
		if (1 == count)
		{
			DragQueryFileW(hDropInfo, 0, file_path, path_length);
			SetWindowTextW(file_path);
			DragFinish(hDropInfo);		// After successful drag and drop, release memory
		}
		else
		{
			DragFinish(hDropInfo);
		}

		delete[] file_path;
	}

	CEdit::OnDropFiles(hDropInfo);
}
