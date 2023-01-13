#define _GNU_SOURCE
#include <stdlib.h>
#include "libncurses/curses.h"
#include <signal.h>
#include <locale.h>
#include <wchar.h> 		/* Широкие символы */
#include <sys/time.h>
#include "extra/extra.h"


WINDOW *window;
const wchar_t **arrayDigits[11] = {zero, one, two, three, four, five, six, seven, eight, nine, colon};
size_t widthDigits[11]; /* Ширина первой строки цифр и символа ':' */
struct timeval tv;
struct timezone tz;

void init(void);
void finishSig(int n);
void finish(void);
int prrTime(int m, int s, int initialM, int initialS, int next);
void prrWrite(int Y, int X, const wchar_t **str); 					/* Печать цифр */
void timeInArray(int m, int s, int *array); 						/* Преобразует время в цифры массива */

int main(void) /* "▒▓█" */
{
	int checkPrrTime;
	
	setlocale(LC_ALL, "");
	init();
	move(0, 0);
	checkPrrTime = prrTime(0, 0, 0, 0, TRUE);
	if (checkPrrTime == -1)
	{
		addstr("Ошибка вывода времени!!!\n");
		refresh();
		napms(1500);
	}
	finish();	
	return 0;
}
void init(void)
{
	window = initscr(); 		/* 	Инициализация 							*/
	savetty(); 					/* 	Сохраняем текущие настройки 			*/
	nonl(); 					/* 	Не переходит на новую строку 			*/
	cbreak(); 					/* 	Отмена построчной буферизации 			*/
	noecho(); 					/* 	Не отображаются символы когда
									печатаем на клавиатуре 					*/
	timeout(0); 				/* 	Не блокирующее чтение
									(0 - неблокирующее, -1 - блокирующее) 	*/
	leaveok(stdscr, TRUE); 		/* 	Возможность произвольно двигать курсор	*/
	curs_set(0); 				/* 	Спрятать курсор							*/
	signal(SIGINT, finishSig); 	/* 	Ctrl + C								*/
	for (int i = 0; i < 11; i++)
		widthDigits[i] = wcslen(arrayDigits[i][0]); /* strlen for wchar_t */
}
void finishSig(int n)
{
	finish();
}
void finish(void)
{
	curs_set(1);
	clear(); 				/* 	Очистка 							*/
	refresh(); 				/*	 экрана 							*/
	resetty(); 				/* 	Восстанавливаем текущие настройки 	*/
	endwin();
	exit(0);
}
int prrTime(int m, int s, int initialM, int initialS, int next) /* Таймер / секундомер */
{
	char input;
	int valueDigits[4]; /* 22:45 */
	int startY = (maxY / 2) - 3, startX = (maxX / 2) - 2, indentDigit = 1; /* Положение цифр на экране и отступ между цифрами */
	long int timeSec;

	if (s >= 60 || m >= 100) 	/* Возвращаем ошибку если неправильное время */
		return -1;

	timeInArray(m, s, valueDigits); /* Записываем минуты и секунды в массив */

	/* Выводим на экран начальное значение 	*/
	clear(); 							/* Очищаем экран от предыдущих цифр */
	prrWrite(startY, startX, colon); 	/* Центр */
	prrWrite(startY, startX - (widthDigits[0] * 2 + indentDigit * 2), arrayDigits[0]); 					/* Минуты, 	[0] */
	prrWrite(startY, startX - (widthDigits[0] + indentDigit), arrayDigits[0]); 							/* 			[1] */
	prrWrite(startY, startX + (widthDigits[10] + indentDigit), arrayDigits[0]); 						/* Секунды, [2] */
	prrWrite(startY, startX + (widthDigits[10] + widthDigits[0] + indentDigit * 2), arrayDigits[0]); 	/* 			[3] */
	refresh();
	/* ------------------------------------ */
	
	gettimeofday(&tv, &tz);
	timeSec = tv.tv_sec;
	while ((input = wgetch(stdscr)) != 'q')
	{
		gettimeofday(&tv, &tz); 				/* Замеряем время */
		
		if (tv.tv_sec > timeSec) 				/* Если прошла секунда */
		{
			gettimeofday(&tv, &tz);
			timeSec = tv.tv_sec; 				/* Обновляем время */
			valueDigits[3]++;
			if (valueDigits[3] >= 10) 			/* Секунды в дестяки секунд */
			{
				valueDigits[2]++; valueDigits[3] = 0;
			}
			if (valueDigits[2] >= 6) 			/* Десятки секунд в минуты */
			{
				valueDigits[1]++; valueDigits[2] = 0;
			}
			if (valueDigits[1] >= 10) 			/* Минуты в десятки минут */
			{
				valueDigits[0]++; valueDigits[1] = 0;
			}
			clear(); 							/* Очищаем экран от предыдущих цифр */
			prrWrite(startY, startX, colon); 	/* Центр */
			prrWrite(startY, startX - (widthDigits[valueDigits[1]] + widthDigits[valueDigits[0]] + indentDigit * 2), arrayDigits[valueDigits[0]]); 	/* Минуты, 	[0] */
			prrWrite(startY, startX - (widthDigits[valueDigits[1]] + indentDigit), arrayDigits[valueDigits[1]]); 									/* 			[1] */
			prrWrite(startY, startX + (widthDigits[10] + indentDigit), arrayDigits[valueDigits[2]]); 												/* Секунды, [2] */
			prrWrite(startY, startX + (widthDigits[10] + widthDigits[valueDigits[2]] + indentDigit * 2), arrayDigits[valueDigits[3]]); 				/* 			[3] */
			refresh();
		}
	}

	return 1;
}
void prrWrite(int Y, int X, const wchar_t **str) /* Печать цифр */
{
	for (int i = 0; i < 6; i++)
	{
		move(Y, X);
		addwstr(str[i]);
		Y++;
	}
}
void timeInArray(int m, int s, int *array) /* Помещаем время в массив */
{
	array[0] = m / 10;
	array[1] = m % 10;
	array[2] = s / 10;
	array[3] = s % 10;
}
