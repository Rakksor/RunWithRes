#include <stdio.h>
#include <windows.h>

void print_help() {
	printf(	"\nusage: runwithres <width> <height> <path to program> <arguments>\n\n"\
			"note that <arguments> is optional and that if you have multiple arguments"\
			" you have to enclose the list of arguments with quotation marks (\")\n\n");
}

void set_resolution(DWORD width, DWORD height) {
	DEVMODE dm;
	dm.dmSize = sizeof(DEVMODE);
	dm.dmDriverExtra = 0;
	dm.dmPelsWidth = width;
	dm.dmPelsHeight = height;
	dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

	LONG return_value = ChangeDisplaySettings(&dm, 0);
		
	if (return_value != DISP_CHANGE_SUCCESSFUL) {
		printf("\nWARNING: unable to change resolution\n");
	}
}

int exec_and_wait(char *file, char *args) {
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = file;
	ShExecInfo.lpParameters = args;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;

	int return_code = ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
	CloseHandle(ShExecInfo.hProcess);

	if (ShExecInfo.hInstApp < 33) {
		printf("\nERROR: the given program could not be executed\n");
	}

	return return_code;
}

int main(int argc, char **argv[]) {
	int return_code = 1;
	DWORD new_width = 0;
	DWORD new_height = 0;

	if (argc > 3) {
		DWORD new_width = strtol(argv[1], NULL, 0);
		DWORD new_height = strtol(argv[2], NULL, 0);

		if (new_width < 1 || new_height < 1) {
			print_help();
			return return_code;
		}

		DWORD old_width = GetSystemMetrics(SM_CXSCREEN);
		DWORD old_height = GetSystemMetrics(SM_CYSCREEN);

		set_resolution(new_width, new_height);
		return_code = exec_and_wait(argv[3], argv[4]);
		set_resolution(old_width, old_height);
	}
	else {
		print_help();
	}

	return return_code;
}