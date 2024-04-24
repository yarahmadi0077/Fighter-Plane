void InitConsole(int ForgC, int BackC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE); /* Handle to current output buffer*/
    COORD coord = {0, 0};
    DWORD count;

    CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;
    SetConsoleTextAttribute(handleConsole, wColor);
    if (GetConsoleScreenBufferInfo(handleConsole, &consoleBuffer))
        FillConsoleOutputAttribute(handleConsole, consoleBuffer.wAttributes, consoleBuffer.dwSize.X * consoleBuffer.dwSize.Y, coord, &count);
    
    return;
}   
    

void move(int y, int x) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}