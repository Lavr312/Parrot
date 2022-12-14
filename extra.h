/*
	help ncurses - <curses.h>

	move(maxY / 2, 0);
	addch('*');
	addstr(str);
	wgetch(stdscr);
	napms(2000);
	mvaddwstr(0, 0, str); - Широкие символы
	wcslen(arrayDigits[i][0]); - strlen for wchar_t
*/

#include <wchar.h>
#define maxX COLS
#define maxY LINES

const wchar_t *colon[6] = {
		L"   ",
		L"██╗",
		L"╚═╝",
		L"██╗",
		L"╚═╝",
		L"   " };
const wchar_t *zero[6] = {
		L" ██████╗ ",
		L"██╔═████╗",
		L"██║██╔██║",
		L"████╔╝██║",
		L"╚██████╔╝",
		L" ╚═════╝ " };
const wchar_t *one[6] = {
		L" ██╗",
		L"███║",
		L"╚██║",
		L" ██║",
		L" ██║",
		L" ╚═╝" };
const wchar_t *two[6] = {
		L"██████╗ ",
		L"╚════██╗",
		L" █████╔╝",
		L"██╔═══╝ ",
		L"███████╗",
		L"╚══════╝" };
const wchar_t *three[6] = {
		L"██████╗ ",
		L"╚════██╗",
		L" █████╔╝",
		L" ╚═══██╗",
		L"██████╔╝",
		L"╚═════╝ " };
const wchar_t *four[6] = {
		L"██╗  ██╗",
		L"██║  ██║",
		L"███████║",
		L"╚════██║",
		L"     ██║",
		L"     ╚═╝" };
const wchar_t *five[6] = {
		L"███████╗",
		L"██╔════╝",
		L"███████╗",
		L"╚════██║",
		L"███████║",
		L"╚══════╝" };
const wchar_t *six[6] = {
		L" ██████╗ ",
		L"██╔════╝ ",
		L"███████╗ ",
		L"██╔═══██╗",
		L"╚██████╔╝",
		L" ╚═════╝ " };
const wchar_t *seven[6] = {
		L"███████╗",
		L"╚════██║",
		L"    ██╔╝",
		L"   ██╔╝ ",
		L"   ██║  ",
		L"   ╚═╝  " };
const wchar_t *eight[6] = {
		L" █████╗ ",
		L"██╔══██╗",
		L"╚█████╔╝",
		L"██╔══██╗",
		L"╚█████╔╝",
		L" ╚════╝ " };
const wchar_t *nine[6] = {
		L" █████╗ ",
		L"██╔══██╗",
		L"╚██████║",
		L" ╚═══██║",
		L" █████╔╝",
		L" ╚════╝ " };
