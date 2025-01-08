// ��    Ī : AIAS(Automatic Inline Alignment System)
// â������ : 1997. 2. 21
// ��    �� : LG����(LG�������� MI Gr. ����ȯ)
// File  �� : Support.h

#ifndef __SUPPORT_H__
#define __SUPPORT_H__

void	RegisterStep(int nStep, void(*pFunc)());
int 	GetStepNo();
double	GetNominal();
double	GetHighLimit();
double	GetLowLimit();
BOOL	CheckValue(double value);
void	SetTimeLimit(int nTime);
BOOL	IsTimeOut();
__inline int	GetInteger();
__inline double	GetDouble();
__inline char*	GetString();
__inline BOOL	GetBoolean();

#endif	//__SUPPORT_H__

